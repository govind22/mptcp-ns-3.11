// Define the model for the Network Animation Viewer
// George F. Riley, Georgia Tech, Spring 2009

#ifndef __ANIM_MODEL_H__
#define __ANIM_MODEL_H__

#include <vector>
#include <map>

#include <QRectF>

class NetView;
class NetWiredLink;
typedef int   NodeId_t;
typedef float Meters_t;
typedef float Time_t;
typedef unsigned Size_t;
#define nil 0

class NetNode {
public:
  typedef enum 
  { // How to represent this node
    CIRCLE, SQUARE, CUSTOM
  } NodeShape_t;
  NetNode();
  NetNode(NodeId_t, Meters_t, Meters_t, Meters_t);
  void SetShape(NodeShape_t);
  void Show();
  void Hide();
  NetWiredLink FindLink(NodeId_t);   // Find link with specified peer
  void AddLink(const NetWiredLink&);
  QPointF GetLoc2d() const;
public:
  std::vector<NetWiredLink> links; // All wired links associated w/ this node
  NodeId_t id;  // Node id
  // Position
  Meters_t x;
  Meters_t y;
  Meters_t z; // Not presently used
  NodeShape_t shape;
  bool     visible;
  bool     exists;
  Time_t   lastPacketLbtxTime; // Just for debugging
};

class NetWiredLink {
public:
  NetWiredLink();
  NetWiredLink(NodeId_t, NodeId_t);
public:
  NodeId_t n1;
  NodeId_t n2;
  bool     exists;
public:
};
  
class NetWiredPacket {
public:
  NetWiredPacket(NodeId_t, NodeId_t, Time_t, Time_t, Time_t, Time_t);
  Time_t fbTx; // first bit tx time
  Time_t lbTx; // last bit tx time
  Time_t fbRx; // first bit rx time
  Time_t lbRx; // last bit rx time
  NodeId_t txNode;  // Transmitting node
  NodeId_t rxNode;  // Receiving Node
};

typedef std::map<NodeId_t, NetNode>           NodeMap_t;
typedef std::vector<NetWiredLink>             LinkVec_t;
typedef std::multimap<Time_t, NetWiredPacket> PktMap_t;

class NetModel 
{ // The interface to add things to the model
public:
  NetModel();
  void SetView(NetView*);
  QRectF GetBoundingRect();
  void   SetBoundingRect(QRectF);
  // Node management
  void AddNode(NodeId_t, Meters_t, Meters_t, Meters_t = 0);    
   NetNode& GetNode(NodeId_t);  // Find node by Id
  // Use a map to map from the node id to the node itself.
  // We use a map to allow the underlying simulation to omit
  // id's (they don't have to be sequential).
  // A node can have multiple ids
  NodeMap_t allNodes;

  // Link Management
  void AddDuplexLink(NodeId_t, NodeId_t);
  NetWiredLink GetLink(NodeId_t, NodeId_t); // Find link from n1 to n2
  LinkVec_t allLinks;

  // Packet Management
  void AddPacket(NodeId_t, NodeId_t,
                             Time_t, Time_t, Time_t, Time_t);
  // All outstanding packets.  These are removed when the current time
  // exceeds the last bit Rx.
  PktMap_t allPkts;
  // Time Management
  void AdvanceTime(Time_t);
public:
  Time_t currentTime;
  NetView* view;
  QPointF  topLeft;     // Minimum x/y for nodes
  QPointF  bottomRight; // Maximum x/y for nodes
};
#endif
