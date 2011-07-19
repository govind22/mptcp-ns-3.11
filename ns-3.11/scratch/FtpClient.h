namespace ns3 {

  class FtpClient : public Application 
  {
  public:
    
    FtpClient ();
    virtual ~FtpClient();
    
    void Configure (Address address, uint32_t transferSize);
    
    void SetTag(std::string tag, int id);
    
    void SetCallBack(void (*startcallback)(Ptr<Node>), void (*stopcallback)(Ptr<Node>));

    bool isActive() {
      return curstate!=DISABLED;
    }

  private:
    virtual void StartApplication (void);  
    virtual void StopApplication (void);
    
    void StartFlow (void);
    void ConnFail (Ptr<Socket> socket);
    void ConnReady (Ptr<Socket> socket);
    void SentData(Ptr<Socket> socket, uint32_t datasent);

    //App params
    Address m_destaddr;
    uint32_t m_transsize;
    
    // Id Tags
    std::string m_tag;
    int m_id;
    
    // Callback
    void (*m_flowstartcallback)(Ptr<Node>);
    void (*m_flowstopcallback)(Ptr<Node>);
    
    //Counters
    uint32_t m_txbufmax;
    uint32_t m_cursent;
       
    enum States {DISABLED, CONNECTING, SENDING, WAITING};
    States curstate;

    Ptr<Socket> m_socket;
  };
  
  FtpClient::FtpClient () 
  {
    m_socket = 0;
    curstate = DISABLED;
    m_flowstartcallback = NULL;
    m_flowstopcallback = NULL;
    m_tag = "X";
    m_id = -1;
  }

  FtpClient::~FtpClient()
  {}

  void
  FtpClient::Configure (Address address, uint32_t transferSize) {
    m_destaddr = address;
    m_transsize = transferSize;
  }
  
  void 
    FtpClient::SetTag(std::string tag, int id)
  { 
    m_tag = tag;
    m_id = id;
  }
  
  void 
    FtpClient::SetCallBack(void (*startcallback)(Ptr<Node>),void (*stopcallback)(Ptr<Node>) )
  { 
    m_flowstartcallback = startcallback;
    m_flowstopcallback = stopcallback;
  }

 
 
  void
  FtpClient::StartApplication (void)
  {
    curstate = WAITING;
    StartFlow();
  }

  void 
  FtpClient::StopApplication (void)
  {
    curstate = DISABLED;

    if(m_socket) {
      m_socket->Close();
      m_socket = 0;
    }
  }

  void 
  FtpClient::StartFlow (void)
  {
    if(curstate != WAITING) {
      return;
    }

    curstate = CONNECTING;

    //Create socket
    m_socket = Socket::CreateSocket (GetNode(), TcpSocketFactory::GetTypeId());

    //m_socket->SetPriority(7);
    
    //Create callbacks
    //m_socket->SetConnectCallback(MakeCallback(&FtpClient::ConnReady, this),
		//	       MakeNullCallback<void, Ptr<Socket> > ());

    m_socket->SetConnectCallback(MakeCallback(&FtpClient::ConnReady, this),
			       MakeCallback(&FtpClient::ConnFail, this));
    m_socket->Bind();
    m_socket->Connect(m_destaddr);
    if (m_flowstartcallback != NULL)
    {
      m_flowstartcallback(GetNode());
      m_flowstartcallback=NULL;
      //if (GetNode()->GetId() == 0) std::cout << "TEST: FTPC: START Flow "<< m_tag <<"\t" << m_id << "\tat node " << GetNode()->GetId() << "\n";
    }
  }


  void
  FtpClient::ConnFail(Ptr<Socket> socket) {
      std::cout << m_tag <<"\t" << m_id <<"\t\tTX: " << "-" << "\tTPT: " << "-" << "\tStart: " << "-" << "\tStop: " << ((double)Now().GetNanoSeconds()/1000000) << "\tT: " << "10000" << std::endl; 
  }
  void
  FtpClient::ConnReady(Ptr<Socket> socket) {

    if(curstate == DISABLED) {
      socket->Close();
    }

    if(curstate != CONNECTING) {
      return;
    }

    curstate = SENDING;

    //Create callback
    socket->SetDataSentCallback(MakeCallback(&FtpClient::SentData, this));

    //Initialize counters
    m_cursent = 0;
    m_txbufmax = socket->GetTxAvailable();
    SentData (socket, 0);
  }

  void
  FtpClient::SentData(Ptr<Socket> socket, uint32_t dataSent) {
    if(curstate == DISABLED) {
      if(socket->GetTxAvailable() == m_txbufmax) {
	socket->Close();
      }
    }

    if(curstate != SENDING) {
      return;
    }
    
    //If done with flow
    if(m_transsize == m_cursent) {
      //Wait until tx buffer is empty
      if(socket->GetTxAvailable() == m_txbufmax) {
	curstate = DISABLED;
	socket->Close();
      }
      if (m_flowstopcallback != NULL)
      {
        m_flowstopcallback(GetNode());
        m_flowstopcallback=NULL;
        //if (GetNode()->GetId() == 0) std::cout << "TEST: FTPC: STOP Flow "<< m_tag <<"\t" << m_id << "\tat node " << GetNode()->GetId() << "\n";
      }
      return;
    }

    //Otherwise send next batch
    uint32_t bufsize;
    bufsize = socket->GetTxAvailable() < (m_transsize - m_cursent) ? socket->GetTxAvailable() : (m_transsize - m_cursent); 

    //If have room to send
    if(bufsize > 0) {
      Ptr<Packet> packet = Create<Packet>(bufsize);
      socket->Send(packet);
      m_cursent += bufsize;
    }
  }
}
