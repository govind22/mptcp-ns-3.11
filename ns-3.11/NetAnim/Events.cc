// Manage future events for the Network Animator
// George F. Riley, Georgia Tech, Spring 2009

#include <iostream>
#include <sstream>
#include "Events.h"

using namespace std;

static TSDeq_t events;  // List of pending events
static Time_t  infTime = 1E300; // Infinite time
static int     fHandle = -1;    // File handle to read if non-negative
#define CBUF_SIZE 5000
static char    cbuf[CBUF_SIZE]; // Circular buffer for fHandle interface
static int     first = 0;
static int     in = 0;
static int     out = 0;
static int     limit = first + CBUF_SIZE;

// Circular buffer management, all static
static bool Empty()
{
  return in == out;
}

static int Advance(int i)
{
  if ((i + 1) == limit) return first;
  return i + 1;
}

#ifdef NOT_USED
// Keep compiler happy.  Uncomment if needed
static int Decrement(int i)
{
  if (i == 0) return limit - 1;
  return i - 1;
}
#endif

static int SpaceAvailable()
{
  if (in == out) return limit - 1; // BUffer is empty
  if (in > out)  return limit - (in - out) - 1;
  return (out - in) - 1;
}

#ifdef NOT_USED
// Keep compiler happy.  Uncomment if needed
static int DataAvailable()
{
  if (in >= out) return in - out;
  return limit - (out - in );
}
#endif

static bool StringAvailable()
{
  if (Empty()) return false;
  // Look for eol
  int out1 = out;
  while(out1 != in)
    {
      if (cbuf[out1] == '\n') return true; // Found it
      out1 = Advance(out1);
    }
  return false;
}

string GetString()
{ // String must be available
  char b[CBUF_SIZE];
  char* p = b;
  int  out1 = out;
  while(cbuf[out1] != '\n')
    {
      *p++ = cbuf[out1];
      out1 = Advance(out1);
    }
  *p++ = 0;            // Terminate string
  out = Advance(out1); // Set the new out pointer
  return string(b);
}

string PeekString()
{ // String must be available.
  // Return string but don't advance out
  char b[CBUF_SIZE];
  char* p = b;
  int  out1 = out;
  while(cbuf[out1] != '\n')
    {
      *p++ = cbuf[out1];
      out1 = Advance(out1);
    }
  *p++ = 0;            // Terminate string
  return string(b);
}

void ReadFromHandle()
{
  if (SpaceAvailable() == 0) return;
  char b[CBUF_SIZE];
  int n = read(fHandle, b, SpaceAvailable());
  b[n] = 0; // debug
  
  if (n <= 0) return;
  int in1 = in;
  for (int i = 0; i < n; ++i)
    {
      cbuf[in1] = b[i];
      in1 = Advance(in1);
    }
  in = in1;
}
// End of circular queue code
      
void ReadEventsFromHandle(Time_t now)
{
  if (fHandle < 0) return;
  ReadFromHandle(); // First fill the CQ with any new data
  while(StringAvailable())
    {
      string st = PeekString();
      Time_t t1 = GetEventTime(st);
      if (t1 > now) return; // Don't process events in the future
      st = GetString();
      AddEvent(t1, st);
    }
}

void SetEventsFileHandle(int h)
{ // File hand to read for future events (in string format)
  fHandle = h;
}

void AddEventsFromFile(ifstream& ifs)
{
  while(ifs)
    {
      string line;
      getline(ifs, line);
      Time_t t = GetEventTime(line);
      AddEvent(t, line);
    }
}


int ProcessAllPending(NetModel* m, Time_t now)
{
  ReadEventsFromHandle(now);
  int nProcessed = 0;
  while(true)
    {
      Time_t earliest = EarliestEventTime();
      if (earliest > now) return nProcessed; // No more to process at this time
      TSPair_t ev = GetEarliestEvent();
      //cout << "Time " << ev.first
      //     << " ev " << ev.second << endl;
      ProcessEvent(m, ev);
      nProcessed++;
    }
}

void AddEvent(Time_t t, const string& s)
{
  events.push_back(make_pair(t, s));
}

Time_t GetEventTime(const string& s)
{ // Get the event time from the string
  istringstream iss(s);
  Time_t t;
  iss >> t;
  return t;
}

Time_t EarliestEventTime()
{ // Get time of earliest event
  if (events.empty()) return infTime;
  return events.front().first;
}

TSPair_t GetEarliestEvent()
{ // Get and remove earliest event
  TSPair_t e = events.front();
  events.pop_front();
  return e;
}

void ProcessEvent(NetModel* m, const TSPair_t& e)
{
  istringstream iss(e.second);
  
  Time_t time;
  char   action;
  int    id;
  double x;
  double y;
  int    n1;
  int    n2;
  Time_t t1;
  Time_t t2;
  Time_t t3;
  iss >> time >> action;
  switch (action) 
    {
    case 'N' : // Node
      iss >> id >> x >> y;
      m->AddNode(id, x, y, 0);
      //cout << "Added node " << id 
      // << " x " << x << " y " << y << endl;
      break;
    case 'L' : // Link
      iss >> n1 >> n2;
      m->AddDuplexLink(n1, n2);
      break;
    case 'P' : // Packet
      iss >> n1 >> n2 >> t1 >> t2 >> t3;
      m->AddPacket(n1, n2, time, t1, t2, t3);
      break;
    default:
      break;
    }
}

