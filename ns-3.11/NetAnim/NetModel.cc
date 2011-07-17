// Implementation of the Network Animation Viewer Model
// George F. Riley, Georgia Tech, Spring 2009

#include <iostream>
#include "NetModel.h"

using namespace std;

// NetNode data/methods
NetNode::NetNode()
  : id(-1), x(0), y(0), z(0), shape(CIRCLE),
    visible(false), exists(false), lastPacketLbtxTime(0)
{ // Default constructor is only used when indexing the map of
  // all nodes with an invalid id; this gives a node with exists = false.
}

NetNode::NetNode(NodeId_t id0, Meters_t x0, Meters_t y0, Meters_t z0)
  : id(id0), x(x0), y(y0), z(z0), shape(CIRCLE),
    visible(true), exists(true), lastPacketLbtxTime(0)
{
}

void NetNode::SetShape(NodeShape_t s)
{
  shape = s;
}


void NetNode::Show()
{
  visible = true;
}

void NetNode::Hide()
{
  visible = false;
}

NetWiredLink NetNode::FindLink(NodeId_t n2Id)
{
  if (exists)
    {
      for (Size_t i = 0; i < links.size(); ++i)
        {
          if (links[i].n2 == n2Id) return links[i];
        }
    }
  // Not found, return empty link
  return NetWiredLink();
}

void NetNode::AddLink(const NetWiredLink& lk)
{
  links.push_back(lk);
}

QPointF NetNode::GetLoc2d() const
{
  return QPointF(x, y);
}

NetWiredLink::NetWiredLink()
  : exists(false)
{ // Allow an erroneous return from GetLink
}

NetWiredLink::NetWiredLink(NodeId_t nd1, NodeId_t nd2)
  : n1(nd1), n2(nd2), exists(true)
{
}

// Wired Packet Members and Methods

NetWiredPacket::NetWiredPacket(NodeId_t n1, NodeId_t n2,
                                 Time_t fbTx0, Time_t lbTx0,
                                 Time_t fbRx0, Time_t lbRx0)
  : fbTx(fbTx0), lbTx(lbTx0), fbRx(fbRx0), lbRx(lbRx0),
    txNode(n1), rxNode(n2)
{
}

// NetModel methods

// Constructor
NetModel::NetModel() : currentTime(0), view(nil)
{
  // Nothing else needed  
}

void NetModel::SetView(NetView* v)
{
  view = v;
}

QRectF NetModel::GetBoundingRect()
{
  QRectF br(topLeft, QPointF());
  // Add 10% borders
  float w = bottomRight.x() - topLeft.x();
  float h = bottomRight.y() - topLeft.y();
  br.setWidth (w * 1.1);
  br.setHeight(h * 1.1);
  br.moveTopLeft(topLeft - QPointF(w * 0.05, h * 0.05));
  return br;
}

// SetBoundingRect sets the minimum size of the network node placement.
// It will grow as needed as nodes are added
void NetModel::SetBoundingRect(QRectF br)
{
  topLeft = br.topLeft();
  bottomRight = br.bottomRight();
}

void NetModel::AddNode(NodeId_t id,
                             Meters_t x, Meters_t y, Meters_t z)
{
  //cout << "NN " << 0.0 << " " << x0 << " " << y0 << endl;
  if (topLeft == QPointF(0,0) && bottomRight == QPointF(0,0))
    { // First node, set ul and lr
      topLeft = QPointF(x, y);
      bottomRight = QPointF(x, y);
    }
  else
    {
      if (x < topLeft.x())  topLeft.setX(x);
      if (y < topLeft.y())  topLeft.setY(y);
      if (x > bottomRight.x()) bottomRight.setX(x);
      if (y > bottomRight.y()) bottomRight.setY(y);
    }
  allNodes[id] = NetNode(id, x, y, z);;
}

NetNode& NetModel::GetNode(NodeId_t id)
{ // Finds a node by id
  return allNodes[id];
}


void NetModel::AddDuplexLink(NodeId_t n1Id, NodeId_t n2Id)
{
  NetNode& n1 = GetNode(n1Id);
  NetNode& n2 = GetNode(n2Id);
  if (!n1.exists || !n2.exists)
    {
      cout << "NetModel::AddDuplexLink::AddDuplexLink failed" << endl;
      return;
    }
  allLinks.push_back(NetWiredLink(n1Id, n2Id));
  n1.AddLink(allLinks.back());
  allLinks.push_back(NetWiredLink(n2Id, n1Id));
  n2.AddLink(allLinks.back());
}

NetWiredLink NetModel::GetLink(NodeId_t n1, NodeId_t n2)
{
  NetNode& n = GetNode(n1);
  return n.FindLink(n2);
}


void NetModel::AddPacket(NodeId_t n1Id, NodeId_t n2Id,
                                  Time_t fbTx, Time_t lbTx,
                                  Time_t fbRx, Time_t lbRx)
{
  allPkts.insert(
          make_pair(lbRx, 
                    NetWiredPacket(n1Id, n2Id, fbTx, lbTx, fbRx, lbRx)));
}

// Time Management
void NetModel::AdvanceTime(Time_t t)
{
  currentTime += t;
  // Remove pkts that are in the past
  while(!allPkts.empty())
    {
      multimap<Time_t, NetWiredPacket>::iterator first = allPkts.begin();
      if (first->first > currentTime) return; // Still in future
      // Remove it
      allPkts.erase(allPkts.begin());
    }
}


  
