#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>

// Socket related includes for the sockets interface
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QResizeEvent>

#include "NetView.h"
#include "NetModel.h"
#include "Events.h"

using namespace std;

int main(int argc, char** argv)
{
  QApplication a(argc, argv);
  NetView*  v = NetView::Create(&a);
  NetModel* m = v->GetNetModel();
  v->SetViewSize(1500, 1000);
  //v->SetViewSize(768, 768);
  v->SetUpdateInterval(0.001); // 1ms
  if (argc == 2)
    { // Read in all events from the specified file
      ifstream ifs(argv[1]);
      if (!ifs)
        {
          cout << "Can't openlocation file " << argv[1] << endl;
          exit(1);
        }
      AddEventsFromFile(ifs);
    }
  else if (argc == 3)
    { // argv[1] is host name, argv[2] is port
      int s = socket(AF_INET, SOCK_STREAM, 0);
      struct hostent* pHE = gethostbyname(argv[1]);
      if (pHE == 0)
        {
          cout << "Can't look up host " << argv[1] << endl;
          exit(2);
        }
      int port = atol(argv[2]);
      struct sockaddr_in addr;
      memcpy(&addr.sin_addr, pHE->h_addr, pHE->h_length);
      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      cout << "Connecting to " << inet_ntoa(addr.sin_addr)
           << " port " << port << endl;
      int c = connect(s, (struct sockaddr*)&addr, sizeof(addr));
      if (c < 0)
        {
          cout << "Can't connect" << endl;
          exit(3);
        }
      SetEventsFileHandle(s);
    }
  else
    {
      // Create a 2d grid
      int nrows = 10;
      int ncols = 10;
      int nPkts = 100000;
  
#define NID(r,c) (r)*ncols+(c)
#define ROW(i) (i)/ncols
#define COL(i) (i)%ncols
      for (int r = 0; r < nrows; ++r)
        {
          for (int c = 0; c < ncols; ++c)
            {
              m->AddNode(NID(r,c), c, r, 0);
              if (r > 0) m->AddDuplexLink(NID(r,c), NID(r-1,c));
              if (c > 0) m->AddDuplexLink(NID(r,c), NID(r, c-1));
            }
        }
      Time_t pktTime = 0;
      for (int i = 0; i < nPkts; ++i)
        {
          int txNode = (int)(drand48()*m->allNodes.size()); // Random node id
          int nd = (int)(drand48() * 4); // 0 left, 1 up, 2 right, 3 down
          int txrow = ROW(txNode);
          int txcol = COL(txNode);
          int rxNode = -1;
          switch(nd) 
            {
            case 0:
              if (txcol > 0) rxNode = NID(txrow, txcol-1);
              break;
            case 1:
              if (txrow > 0) rxNode = NID(txrow - 1, txcol);
              break;
            case 2:
              if (txcol < (ncols - 1)) rxNode = NID(txrow, txcol + 1);
              break;
            case 3:
              if (txrow < (nrows - 1)) rxNode = NID(txrow + 1, txcol);
              break;
            }
          if (rxNode >= 0)
            {
              Time_t pt = drand48() * 0.050;            // Random time 0 - 10ms
              Time_t lastPt = m->GetNode(txNode).lastPacketLbtxTime;
              Time_t thisPt = lastPt + pt;
              m->AddPacket(txNode, rxNode,
                           thisPt, thisPt + 0.010,
                           thisPt + 0.100, thisPt + 0.110);
              m->GetNode(txNode).lastPacketLbtxTime = thisPt + 0.010;
              pktTime = thisPt;
            }
        }
    }
  a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
  v->StartAnimation(false);
  return a.exec();
}

  
