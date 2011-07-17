namespace ns3 {
  NS_LOG_COMPONENT_DEFINE ("FtpServer");

  class FtpServer : public Application 
  {
  public:
    
    FtpServer ();
    virtual ~FtpServer();
    
    void Configure (uint64_t, uint16_t, Time, bool);
    
  private:
    virtual void StartApplication (void);  
    virtual void StopApplication (void);

    void HandleRead (Ptr<Socket> socket);
    void HandleClose (Ptr<Socket> socket);
    void HandleAccept (Ptr<Socket> s, const Address& from);

    Ptr<Socket> m_socket;

    //Config params
    uint64_t m_maxRxBytes;
    uint16_t m_port;
    bool m_report;

    //Counters
    uint64_t m_curRxBytes;
    Time m_starttime;

    enum States {DISABLED, LISTENING, RECEIVING};
    States curstate;
  };

  FtpServer::FtpServer() 
    {
      curstate = DISABLED;
    }
  
  FtpServer::~FtpServer()
    {}
  

  void
    FtpServer::Configure(uint64_t maxrxbytes, uint16_t port, Time starttime, bool report)  {
    m_maxRxBytes = maxrxbytes;
    m_port = port;
    m_report = report;
    m_starttime = starttime;
  }
  
  void
    FtpServer::StartApplication (void)
  {
    if(curstate != DISABLED) {
      return;
    }
    
    curstate = LISTENING;
    
    Address laddr (InetSocketAddress(Ipv4Address::GetAny(), m_port));
    m_socket = Socket::CreateSocket (GetNode(), TcpSocketFactory::GetTypeId());
    
    m_socket->SetAcceptCallback (
				 MakeNullCallback<bool, Ptr<Socket>, const Address &> (),
				 MakeCallback(&FtpServer::HandleAccept, this));
    
    //m_socket->SetPriority(4);
    m_socket->Bind(laddr);
    m_socket->Listen();   
  }

  void 
    FtpServer::StopApplication (void)
  {
    curstate = DISABLED;

    m_socket->Close();
    m_socket = 0;
  }
  
  void 
    FtpServer::HandleRead (Ptr<Socket> socket)
  {
    if(curstate == DISABLED) {
      socket->Close();
    }

    if(curstate != RECEIVING) {
      return;
    }

    Address from;
    Ptr<Packet> packet;
    while (packet = socket->RecvFrom (from))
      {
	m_curRxBytes += packet->GetSize();
	//Fixes problem with close callback not being called
	if(m_curRxBytes >= m_maxRxBytes) {
	  HandleClose(socket);
	  return;
	}
      }
  }

  void 
    FtpServer::HandleClose (Ptr<Socket> socket)
  {

    if(curstate != RECEIVING) {
      return;
    }

    curstate = DISABLED;

    Time m_endtime = Simulator::Now();
    double diff_us = m_endtime.GetMicroSeconds() - m_starttime.GetMicroSeconds();

    if(m_report) {
      //TX Size (MB), Rate (Mbps), Duration (s), End time (s)
      std::cout << ((double)m_curRxBytes)/(1024*1024) << "\t" << ((double)m_curRxBytes)*8/diff_us << "\t" << diff_us/1000000 << "\t" << ((double)m_endtime.GetMicroSeconds())/1000000 << std::endl; 
    }
 
    socket->Close();
  }
 
  void 
    FtpServer::HandleAccept (Ptr<Socket> s, const Address& from)
  {
    if(curstate != LISTENING) {
      s->Close();
      return;
    }

    curstate = RECEIVING;

    //Reset values
    m_curRxBytes = 0;

    //s->SetPriority(4);

    s->SetRecvCallback (MakeCallback(&FtpServer::HandleRead, this));
    s->SetCloseCallbacks (
			  MakeCallback(&FtpServer::HandleClose, this),
			  MakeNullCallback < void,Ptr<Socket> > ());

  }
}
