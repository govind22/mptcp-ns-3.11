// Network Animation View
// George F. Riley, Georgia Tech, Spring 2009

#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

#include <QApplication>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include <QLabel>
#include <QScrollArea>
#include "NetView.h"
#include "Events.h"

using namespace std;

NetView::NetView(NetModel* m0, QWidget* mw)
  : w(768), h(768), minW(w), minH(h),
    paintPM(nil), historyIndex(-1), m(m0), mainWidget(mw), sa(nil),
    simTimeWidget(nil), updateRate(nil), backupSlider(nil),
    updateInterval(0.001), maxHistorySize(1000),
    nodeRadius(5), linkWidth(1), paused(true), framesPerSecond(24)
{
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(TimeToUpdate()));
  recordTimer = new QTimer();
  connect(recordTimer, SIGNAL(timeout()), this, SLOT(TimeToRecord()));
  
  updateRates[0]  = 0.000001;
  updateRates[1]  = 0.000002;
  updateRates[2]  = 0.000004;
  updateRates[3]  = 0.000008;
  updateRates[4]  = 0.000016;
  updateRates[5]  = 0.000032;
  updateRates[6]  = 0.000064;
  updateRates[7]  = 0.000125;
  updateRates[8]  = 0.000250;
  updateRates[9]  = 0.000500;
  updateRates[10] = 0.001000;
  updateRates[11] = 0.002000;
  updateRates[12] = 0.004000;
  updateRates[13] = 0.008000;
  updateRates[14] = 0.016000;
  updateRates[15] = 0.032000;
  updateRates[16] = 0.064000;
  updateRates[17] = 0.125000;
  updateRates[18] = 0.250000;
  updateRates[19] = 0.500000;
  updateRates[20] = 1.000000;

}

void NetView::SetUpdateInterval(Time_t ui, bool moveSlider)
{
  updateInterval = ui;
  if (timer && !paused)
    {
      timer->stop();
      int ms = (int)(ui * 1000.0);
      if (ms == 0) ms = 1;
      //cout << "Setting timer interval to " << ms << " ms" << endl;
      timer->setInterval(ms);
      timer->start();
    }
  if (moveSlider)
    {
      int i = 0;      
      for (; i < MAX_SLIDER-1; ++i)
        {
          if (updateRates[i] >= ui) break; // found it
        }
      updateRateSlider->setValue(i);
    }
  ostringstream oss;
  oss.precision(6);
  oss << fixed << setw(8) << ui;
  updateRate->setText(oss.str().c_str());
}

void NetView::StartAnimation(bool unpause)
{
  update(); // Show the time zero state
  if (unpause)
    {
      paused = false;
      int ms = (int)(updateInterval * 1000.0);
      if (ms == 0) ms = 1;
      timer->setInterval(ms);
      //cout << "Setting timer interval to " << ms << " ms" << endl;
      //timer->setInterval(50); // very slow for debugging
      timer->start();
    }
}

void NetView::SetViewSize(int w0, int h0)
{
  minW = w0;
  minH = h0;
  if (w < minW) w = minW;
  if (h < minH) h = minH;
  setMinimumSize(minW, minH);
  cout << "Setting min size, minw " << minW << ", minh " << minH << endl;
  if (paintPM)
    {
      delete paintPM;
      paintPM = nil;
    }
}

NetModel* NetView::GetNetModel()
{
  return m;
}

void NetView::UpdateSimTime(Time_t now)
{
  //cout << "Updating simtimewidget to " << now << endl;
  ostringstream oss;
  oss.precision(6);
  oss << fixed << setw(8) << now;
  simTimeWidget->setText(oss.str().c_str());
}

void NetView::AddHistory(Time_t now, NetModel* nm)
{
  // Add the history for backing up the simulation
  if (history.size() == maxHistorySize)
    { // Delete front
      //pair<Time_t, QPixmap*>& front = history.front();
      //delete front.second; // Delete the pixmap
      history.pop_front();
    }
  history.push_back(make_pair(now, *nm));
}

// Inherited from QWidget
void NetView::paintEvent(QPaintEvent*)
{
  if (!paintPM)
    { // Should not happen
      //cout << "Creating new pixmap" << endl;
      paintPM = new QPixmap(minW, minH);
      paintPM->fill();
      mainWidget->resize(minW, minH);
    }
  QPainter p(this);
  p.drawPixmap(QPoint(0,0), *paintPM);
}

void NetView::resizeEvent(QResizeEvent*)
{
  //if (rev->size().width()  > minW) minW = rev->size().width();
  //if (rev->size().height() > minH) minH = rev->size().height();
  //cout << "Hello from resize event, w " << w
  //     << " h " << h << endl;
}

void NetView::update()
{
  NetModel* nm = m; // Use current net model unless history

  if (historyIndex >= 0)
    {
      nm = &history[historyIndex].second;
    }
  else
    { // Need to process any new events
      ProcessAllPending(nm, nm->currentTime);
    }

  viewRect = nm->GetBoundingRect();
  //cout << "Hello from update" << endl;
  if (!paintPM)
    {
      paintPM = new QPixmap(minW, minH);
    }
  paintPM->fill();
  // Draw the nodes, links, and packets here
  QPainter p(paintPM);
  p.setRenderHints(QPainter::Antialiasing);
  QBrush blackBrush(Qt::black);
  QPen blackPen(Qt::black);
  p.setPen(blackPen);
  p.setBrush(blackBrush);
  // First the nodes
  QRectF nodeRect(0, 0, nodeRadius * 2, nodeRadius * 2);
  for (NodeMap_t::iterator i = nm->allNodes.begin();
       i != nm->allNodes.end(); ++i)
    {
      NetNode& n = i->second;
      //cout << "Drawing node at x " << n.x << " y " << n.y << endl;
      nodeRect.moveTopLeft(ToPixels(QPointF(n.x, n.y)) - 
                           QPointF(nodeRadius, nodeRadius));
      p.drawRect(nodeRect);
    }
  // Now links
  for (LinkVec_t::size_type i = 0; i < nm->allLinks.size(); ++i)
    {
      NetWiredLink lk = nm->allLinks[i];
      // Since we have two instances of each link, only draw it if
      // the n1 id is < n2 id
      if (lk.n1 < lk.n2)
        {
          NetNode& nn1 = nm->GetNode(lk.n1);
          NetNode& nn2 = nm->GetNode(lk.n2);
          QPointF n1 = ToPixels(nn1.GetLoc2d());
          QPointF n2 = ToPixels(nn2.GetLoc2d());
          //cout << "Drawing Line x0 " << n1.x() << " y0 " << n1.y()
          //     << " x1 " << n2.x() << " y1 " << n2.y() << endl;
          p.drawLine(n1, n2);
        }
    }
  // Now packets
  Time_t currentTime = nm->currentTime;
  QBrush blueBrush(Qt::blue);
  p.setBrush(blueBrush);
  p.setOpacity(0.7); // Allows the wire to show through a bit
  for (PktMap_t::iterator i = nm->allPkts.begin(); i != nm->allPkts.end(); ++i)
    {
      NetWiredPacket pkt = i->second;
      // Make sure still visible (currentTime < lbRx)
      if (pkt.lbRx <= currentTime) continue; // In the past
      if (pkt.fbTx > currentTime) continue;  // In the future

      NetNode& n1 = nm->GetNode(pkt.txNode);
      NetNode& n2 = nm->GetNode(pkt.rxNode);
      QPointF n1Loc = ToPixels(n1.GetLoc2d());
      QPointF n2Loc = ToPixels(n2.GetLoc2d());

      // Set origin to n1
      p.save();
      p.translate(n1Loc);
      // Compute angle to n2
      double dy = n2Loc.y() - n1Loc.y();
      double dx = n2Loc.x() - n1Loc.x();
      double angle = atan2(dy, dx) * 360.0 / (M_PI * 2);;
      //cout << "n2Loc.x " << n2Loc.x() << " n1loc.x " << n1Loc.x()
      //     << " n2Loc.y " << n2Loc.y() << " n1Loc.y " << n1Loc.y()
      //     << endl;
      //cout << "Rotatation angle is " << angle << " degrees " << endl;
      p.rotate(angle);
      
      // Compute distance
      double dist = sqrt(dy * dy + dx * dx);
      // Compute packet transmission time
      Time_t txTime = pkt.lbTx - pkt.fbTx;
      // Adujst if last bit not yet transmitted
      if (pkt.lbTx > currentTime) txTime = currentTime - pkt.fbTx;
      // Adjust if first bit already received
      if (pkt.fbRx < currentTime) txTime -= (currentTime - pkt.fbRx);
      // Propagation delay
      Time_t delay = pkt.fbRx - pkt.fbTx;
      // Compute last bit distance from transmitter
      Time_t lbTime = currentTime - pkt.lbTx; // Relative to current time
      if (lbTime < 0) lbTime = 0;
      double pktWidth = dist * txTime / delay;
      if (pktWidth > 4) pktWidth -= 4; // Some spacing between pkts
      double pktDist = dist * lbTime / delay;
      QRectF pktRect(QPoint(0,0), QPoint(pktWidth, nodeRadius));
      pktRect.moveTopLeft(QPoint(pktDist, -nodeRadius / 2));
      
      p.drawRect(pktRect);
      p.restore();
    }
  QWidget::update();
  // Now add to the history buffer
  if (nm == m)
    { // Add to history only if we are not displaying hsitory
      AddHistory(currentTime, nm);
      // Adjust the backup slider to show how much history is availble
      backupSlider->setValue(history.size());
    }
  
}

// Private methods
QPointF NetView::ToPixels(QPointF loc)
{
  if (viewRect.isEmpty()) viewRect = m->GetBoundingRect();
  double w1 = viewRect.width();
  double h1 = viewRect.height();
  double extraw = 0;
  double extrah = 0;
  double wh = 0;
  if (w1 < h1)
    {
      extraw = (h1-w1)/2;
      wh = h1;
    }
  else
    {
      extrah = (w1-h1)/2;
      wh = w1;
    }
  // Check if all viewrect is zero height (all nodes on same y-coord)
  // or zero width (all nodes on same x-coord)
  if (h1 == 0)
    {
      extrah = minH / 2;
    }
  if (w1 == 0)
    {
      extraw = minW / 2;
    }
  double w2 = (loc.x() - viewRect.left())/ wh;
  double h2 = (loc.y() - viewRect.top()) / wh;
  QPointF ret(w * w2 + extraw, h * h2 + extrah);
  return ret;
}

// Static methods
// These are pixmaps for the VCR Controls
static const char * const play_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"                ",
" ++             ",
" ++++           ",
" ++++++         ",
" ++++++++       ",
" ++++++++++     ",
" ++++++++++++   ",
" +++++++++++++  ",
" +++++++++++++  ",
" ++++++++++++   ",
" ++++++++++     ",
" ++++++++       ",
" ++++++         ",
" ++++           ",
" +++            ",
"                "};


static const char * const pause_xpm[] = {
"16 16 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"                ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"   ++++   ++++  ",
"                "};

static const char *record_xpm[] = {
/* width height ncolors chars_per_pixel */
"32 32 16 1",
/* colors */
"  c #000000000000",
"! c #800000000000",
"# c #000080000000",
"$ c #800080000000",
"% c #000000008000",
"& c #800000008000",
"' c #000080008000",
"( c #800080008000",
") c #c000c000c000",
"* c #ff0000000000",
"+ c #0000ff000000",
", c #ff00ff000000",
"- c #00000000ff00",
". c #ff000000ff00",
"/ c #0000ff00ff00",
"0 c #ff00ff00ff00",
/* pixels */
"                                ",
" 0000000000000000000000000000000",
"  0         0       000000000000",
" 0 --------- ------- 000000 0000",
" 0 ---------          0000 , 000",
"  0          --------     ,, (00",
" 00 - --------------- - - ,, ((0",
"000 - --------------- - - ,, ((0",
"000 - --------------- - - ,, ((0",
"000 - --------------- - - ,, ((0",
"000 - --------------- - - ,, ((0",
"000 - ---------------     ,, ((0",
"0000  -  ----- - - -- (((( , ((0",
"00000 --------------- ((((( (((0",
"000000               (((0000((00",
"0000000(((((((((((((((((00000000",
"00000000(((((((((((((((000000000",
"0000               0000000000000",
"0000 ,0,0,0,0,0,0, (000000000000",
"0000 0,0,0,0,0,0,0 ((00000000000",
"0000 ,0,0               00000000",
"0000 0, , ,0,0,0,0,0,0, (0000000",
"0000 , 0  0,0,0,0,0,0,0 ((000000",
"0000 0, , ,0 0,0,0,0 0, ((000000",
"0000 ,0,0 0 0 0   0 0 0 ((000000",
"0000 0,0, ,0 0,0,0,0 0, ((000000",
"0000      0,0,0,0,0,0,0 ((000000",
"00000(((( ,0,0,0,0,0,0, ((000000",
"000000((( 0,0,0,0,0,0,0 ((000000",
"000000000               ((000000",
"0000000000((((((((((((((((000000",
"00000000000(((((((((((((((000000"
} ;


NetView* NetView::Create(QApplication* app)
{
  QWidget* mw = new QWidget();
  mw->resize(768, 768);
  NetModel* m = new NetModel();
  NetView*  v = new NetView(m, mw);
  mw->setWindowTitle("Network Animator");
  // Try making layouts
  QVBoxLayout* vbox = new QVBoxLayout();
  // Top if the "backup" slider
  v->backupSlider = new QSlider(Qt::Horizontal);
  v->backupSlider->setRange(0, v->maxHistorySize);
  connect(v->backupSlider, SIGNAL(sliderMoved(int)), v, SLOT(BackupSliderMoved(int)));
  vbox->addWidget(v->backupSlider);
  QHBoxLayout* hbox1 = new QHBoxLayout();
  QPushButton* quitButton = new QPushButton("Quit");
  connect(quitButton, SIGNAL(clicked()), app, SLOT(quit()));
  v->updateRate = new QLabel("0.000001");
  // Create the slider
  v->updateRateSlider = new QSlider( Qt::Horizontal);
  v->updateRateSlider->setRange(0, MAX_SLIDER - 1);
  connect( v->updateRateSlider, SIGNAL(sliderMoved(int)), v, SLOT(RateSliderMoved(int)));
  // Create the simtime display
  v->simTimeWidget = new QLabel("0.000000");
  // Put the vcr controls
  QPushButton* play = new QPushButton( QPixmap( play_xpm ), QString());
  connect(play, SIGNAL(clicked()), v, SLOT(Play()));

  QPushButton* pause = new QPushButton( QPixmap( pause_xpm), QString());
  connect(pause, SIGNAL(clicked()), v, SLOT(Pause()));

  QPushButton* record = new QPushButton( QPixmap( record_xpm), QString());
  connect(record, SIGNAL(clicked()), v, SLOT(Record()));

  hbox1->addWidget(quitButton);
  hbox1->addWidget(v->updateRate);
  hbox1->addWidget(v->updateRateSlider);
  hbox1->addWidget(v->simTimeWidget);
  hbox1->addWidget(play);
  hbox1->addWidget(pause);
  hbox1->addWidget(record);
  vbox->addLayout(hbox1);
  v->sa = new QScrollArea();
  v->sa->setWidget(v);
  v->sa->setWidgetResizable(true);
  v->sa->show();
  vbox->addWidget(v->sa);
  vbox->setStretchFactor(v, 20);
  mw->setLayout(vbox);
  mw->show();
  v->show();
  return v;
}

// Slots
void NetView::TimeToUpdate()
{
  //cout << "Advancing time by " << updateInterval;
  m->AdvanceTime(updateInterval);
  //cout << " new time " << m->currentTime << endl;
  UpdateSimTime(m->currentTime);
  update();
}

void NetView::TimeToRecord()
{ // Grab the widget and record here
  QPixmap pixmap = QPixmap::grabWidget(mainWidget);
  static int frameNumber = 0;
  ostringstream oss;
  oss << "ns3anim";
  oss.width(5);
  oss.fill('0');
  oss << frameNumber++;
  oss << ".png";
  pixmap.save(oss.str().c_str());
  //cout << "Saved " << oss.str() 
  //     << " size " << pixmap.width()
  //     << " x " << pixmap.height() << endl;
}

  
void NetView::Play()
{
  paused = false;
  int ms = (int)(updateInterval * 1000.0);
  if (ms == 0) ms = 1;
  timer->setInterval(ms);
  //cout << "Setting timer interval to " << ms << endl;
  //  timer->setInterval(50); // very slow for debugging
  timer->start();
  historyIndex = -1;
}

void NetView::Pause()
{
  paused = true;
  timer->stop();
}

void NetView::Record()
{ // not coded yet
  cout << "Start recording here" << endl;
  if (recordTimer->isActive())
    { // Stop recording if active
      recordTimer->stop();
    }
  else
    {
      int msInterval = 1000/framesPerSecond;
      if (msInterval == 0) msInterval = 1;
      recordTimer->setInterval(msInterval);
      recordTimer->start();
    }
}

  
void NetView::BackupSliderMoved(int value)
{
  paused = true;
  timer->stop();
  int    histSize = history.size();
  if (value >= histSize)
    { // Can't move that way!
      backupSlider->setValue(histSize);
    }
  else
    { // Find the history pixmap and display it
      HistoryPair_t& thisHist = history[(unsigned)value];
      UpdateSimTime(thisHist.first);
      historyIndex = value;
      //historyPM = thisHist.second;
      update();  // Display the history
    }
}

void NetView::RateSliderMoved(int value)
{
  SetUpdateInterval(updateRates[value], false);
}
