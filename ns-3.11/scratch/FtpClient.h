namespace ns3 {

  class FtpClient : public Application 
  {
  public:
    
    FtpClient ();
    virtual ~FtpClient();
    
    void Configure (Address address, uint32_t transferSize);
    
  private:
    virtual void StartApplication (void);  
    virtual void StopApplication (void);
    
    void StartFlow (void);
    void ConnReady (Ptr<Socket> socket);
    void SentData(Ptr<Socket> socket, uint32_t datasent);

    //App params
    Address m_destaddr;
    uint32_t m_transsize;
    
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
  }

  FtpClient::~FtpClient()
  {}

  void
  FtpClient::Configure (Address address, uint32_t transferSize) {
    m_destaddr = address;
    m_transsize = transferSize;
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
    m_socket->SetConnectCallback(MakeCallback(&FtpClient::ConnReady, this),
			       MakeNullCallback<void, Ptr<Socket> > ());

    m_socket->Bind();
    m_socket->Connect(m_destaddr);
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
