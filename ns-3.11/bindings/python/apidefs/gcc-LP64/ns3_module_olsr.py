from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers

def register_types(module):
    root_module = module.get_root()
    
    ## olsr-helper.h: ns3::OlsrHelper [class]
    module.add_class('OlsrHelper', parent=root_module['ns3::Ipv4RoutingHelper'])
    ## olsr-state.h: ns3::OlsrState [class]
    module.add_class('OlsrState')
    module.add_container('std::vector< ns3::olsr::MprSelectorTuple >', 'ns3::olsr::MprSelectorTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::NeighborTuple >', 'ns3::olsr::NeighborTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::TwoHopNeighborTuple >', 'ns3::olsr::TwoHopNeighborTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::LinkTuple >', 'ns3::olsr::LinkTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::TopologyTuple >', 'ns3::olsr::TopologyTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::IfaceAssocTuple >', 'ns3::olsr::IfaceAssocTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::AssociationTuple >', 'ns3::olsr::AssociationTuple', container_type='vector')
    module.add_container('std::vector< ns3::olsr::Association >', 'ns3::olsr::Association', container_type='vector')
    
    ## Register a nested module for the namespace Config
    
    nested_module = module.add_cpp_namespace('Config')
    register_types_ns3_Config(nested_module)
    
    
    ## Register a nested module for the namespace FatalImpl
    
    nested_module = module.add_cpp_namespace('FatalImpl')
    register_types_ns3_FatalImpl(nested_module)
    
    
    ## Register a nested module for the namespace addressUtils
    
    nested_module = module.add_cpp_namespace('addressUtils')
    register_types_ns3_addressUtils(nested_module)
    
    
    ## Register a nested module for the namespace aodv
    
    nested_module = module.add_cpp_namespace('aodv')
    register_types_ns3_aodv(nested_module)
    
    
    ## Register a nested module for the namespace dot11s
    
    nested_module = module.add_cpp_namespace('dot11s')
    register_types_ns3_dot11s(nested_module)
    
    
    ## Register a nested module for the namespace dsdv
    
    nested_module = module.add_cpp_namespace('dsdv')
    register_types_ns3_dsdv(nested_module)
    
    
    ## Register a nested module for the namespace flame
    
    nested_module = module.add_cpp_namespace('flame')
    register_types_ns3_flame(nested_module)
    
    
    ## Register a nested module for the namespace internal
    
    nested_module = module.add_cpp_namespace('internal')
    register_types_ns3_internal(nested_module)
    
    
    ## Register a nested module for the namespace olsr
    
    nested_module = module.add_cpp_namespace('olsr')
    register_types_ns3_olsr(nested_module)
    

def register_types_ns3_Config(module):
    root_module = module.get_root()
    

def register_types_ns3_FatalImpl(module):
    root_module = module.get_root()
    

def register_types_ns3_addressUtils(module):
    root_module = module.get_root()
    

def register_types_ns3_aodv(module):
    root_module = module.get_root()
    

def register_types_ns3_dot11s(module):
    root_module = module.get_root()
    

def register_types_ns3_dsdv(module):
    root_module = module.get_root()
    

def register_types_ns3_flame(module):
    root_module = module.get_root()
    

def register_types_ns3_internal(module):
    root_module = module.get_root()
    

def register_types_ns3_olsr(module):
    root_module = module.get_root()
    
    ## olsr-repositories.h: ns3::olsr::Association [struct]
    module.add_class('Association')
    ## olsr-repositories.h: ns3::olsr::AssociationTuple [struct]
    module.add_class('AssociationTuple')
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple [struct]
    module.add_class('DuplicateTuple')
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple [struct]
    module.add_class('IfaceAssocTuple')
    ## olsr-repositories.h: ns3::olsr::LinkTuple [struct]
    module.add_class('LinkTuple')
    ## olsr-header.h: ns3::olsr::MessageHeader [class]
    module.add_class('MessageHeader', parent=root_module['ns3::Header'])
    ## olsr-header.h: ns3::olsr::MessageHeader::MessageType [enumeration]
    module.add_enum('MessageType', ['HELLO_MESSAGE', 'TC_MESSAGE', 'MID_MESSAGE', 'HNA_MESSAGE'], outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello [struct]
    module.add_class('Hello', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::LinkMessage [struct]
    module.add_class('LinkMessage', outer_class=root_module['ns3::olsr::MessageHeader::Hello'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna [struct]
    module.add_class('Hna', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Association [struct]
    module.add_class('Association', outer_class=root_module['ns3::olsr::MessageHeader::Hna'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid [struct]
    module.add_class('Mid', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc [struct]
    module.add_class('Tc', outer_class=root_module['ns3::olsr::MessageHeader'])
    ## olsr-repositories.h: ns3::olsr::MprSelectorTuple [struct]
    module.add_class('MprSelectorTuple')
    ## olsr-repositories.h: ns3::olsr::NeighborTuple [struct]
    module.add_class('NeighborTuple')
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::Status [enumeration]
    module.add_enum('Status', ['STATUS_NOT_SYM', 'STATUS_SYM'], outer_class=root_module['ns3::olsr::NeighborTuple'])
    ## olsr-header.h: ns3::olsr::PacketHeader [class]
    module.add_class('PacketHeader', parent=root_module['ns3::Header'])
    ## olsr-routing-protocol.h: ns3::olsr::RoutingProtocol [class]
    module.add_class('RoutingProtocol', parent=root_module['ns3::Ipv4RoutingProtocol'])
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry [struct]
    module.add_class('RoutingTableEntry')
    ## olsr-repositories.h: ns3::olsr::TopologyTuple [struct]
    module.add_class('TopologyTuple')
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple [struct]
    module.add_class('TwoHopNeighborTuple')
    module.add_container('std::vector< ns3::olsr::MessageHeader::Hello::LinkMessage >', 'ns3::olsr::MessageHeader::Hello::LinkMessage', container_type='vector')
    module.add_container('std::vector< ns3::olsr::MessageHeader::Hna::Association >', 'ns3::olsr::MessageHeader::Hna::Association', container_type='vector')
    module.add_container('std::vector< ns3::olsr::RoutingTableEntry >', 'ns3::olsr::RoutingTableEntry', container_type='vector')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >', 'ns3::olsr::TopologySet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >*', 'ns3::olsr::TopologySet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TopologyTuple, std::allocator< ns3::olsr::TopologyTuple > >&', 'ns3::olsr::TopologySet&')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >', 'ns3::olsr::MprSet')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >*', 'ns3::olsr::MprSet*')
    typehandlers.add_type_alias('std::set< ns3::Ipv4Address, std::less< ns3::Ipv4Address >, std::allocator< ns3::Ipv4Address > >&', 'ns3::olsr::MprSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >', 'ns3::olsr::MprSelectorSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >*', 'ns3::olsr::MprSelectorSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MprSelectorTuple, std::allocator< ns3::olsr::MprSelectorTuple > >&', 'ns3::olsr::MprSelectorSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >', 'ns3::olsr::Associations')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >*', 'ns3::olsr::Associations*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::Association, std::allocator< ns3::olsr::Association > >&', 'ns3::olsr::Associations&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >', 'ns3::olsr::IfaceAssocSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >*', 'ns3::olsr::IfaceAssocSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::IfaceAssocTuple, std::allocator< ns3::olsr::IfaceAssocTuple > >&', 'ns3::olsr::IfaceAssocSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >', 'ns3::olsr::TwoHopNeighborSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >*', 'ns3::olsr::TwoHopNeighborSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::TwoHopNeighborTuple, std::allocator< ns3::olsr::TwoHopNeighborTuple > >&', 'ns3::olsr::TwoHopNeighborSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >', 'ns3::olsr::DuplicateSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >*', 'ns3::olsr::DuplicateSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::DuplicateTuple, std::allocator< ns3::olsr::DuplicateTuple > >&', 'ns3::olsr::DuplicateSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >', 'ns3::olsr::MessageList')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >*', 'ns3::olsr::MessageList*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::MessageHeader, std::allocator< ns3::olsr::MessageHeader > >&', 'ns3::olsr::MessageList&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >', 'ns3::olsr::NeighborSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >*', 'ns3::olsr::NeighborSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::NeighborTuple, std::allocator< ns3::olsr::NeighborTuple > >&', 'ns3::olsr::NeighborSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >', 'ns3::olsr::AssociationSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >*', 'ns3::olsr::AssociationSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::AssociationTuple, std::allocator< ns3::olsr::AssociationTuple > >&', 'ns3::olsr::AssociationSet&')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >', 'ns3::olsr::LinkSet')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >*', 'ns3::olsr::LinkSet*')
    typehandlers.add_type_alias('std::vector< ns3::olsr::LinkTuple, std::allocator< ns3::olsr::LinkTuple > >&', 'ns3::olsr::LinkSet&')

def register_methods(root_module):
    register_Ns3OlsrHelper_methods(root_module, root_module['ns3::OlsrHelper'])
    register_Ns3OlsrState_methods(root_module, root_module['ns3::OlsrState'])
    register_Ns3OlsrAssociation_methods(root_module, root_module['ns3::olsr::Association'])
    register_Ns3OlsrAssociationTuple_methods(root_module, root_module['ns3::olsr::AssociationTuple'])
    register_Ns3OlsrDuplicateTuple_methods(root_module, root_module['ns3::olsr::DuplicateTuple'])
    register_Ns3OlsrIfaceAssocTuple_methods(root_module, root_module['ns3::olsr::IfaceAssocTuple'])
    register_Ns3OlsrLinkTuple_methods(root_module, root_module['ns3::olsr::LinkTuple'])
    register_Ns3OlsrMessageHeader_methods(root_module, root_module['ns3::olsr::MessageHeader'])
    register_Ns3OlsrMessageHeaderHello_methods(root_module, root_module['ns3::olsr::MessageHeader::Hello'])
    register_Ns3OlsrMessageHeaderHelloLinkMessage_methods(root_module, root_module['ns3::olsr::MessageHeader::Hello::LinkMessage'])
    register_Ns3OlsrMessageHeaderHna_methods(root_module, root_module['ns3::olsr::MessageHeader::Hna'])
    register_Ns3OlsrMessageHeaderHnaAssociation_methods(root_module, root_module['ns3::olsr::MessageHeader::Hna::Association'])
    register_Ns3OlsrMessageHeaderMid_methods(root_module, root_module['ns3::olsr::MessageHeader::Mid'])
    register_Ns3OlsrMessageHeaderTc_methods(root_module, root_module['ns3::olsr::MessageHeader::Tc'])
    register_Ns3OlsrMprSelectorTuple_methods(root_module, root_module['ns3::olsr::MprSelectorTuple'])
    register_Ns3OlsrNeighborTuple_methods(root_module, root_module['ns3::olsr::NeighborTuple'])
    register_Ns3OlsrPacketHeader_methods(root_module, root_module['ns3::olsr::PacketHeader'])
    register_Ns3OlsrRoutingProtocol_methods(root_module, root_module['ns3::olsr::RoutingProtocol'])
    register_Ns3OlsrRoutingTableEntry_methods(root_module, root_module['ns3::olsr::RoutingTableEntry'])
    register_Ns3OlsrTopologyTuple_methods(root_module, root_module['ns3::olsr::TopologyTuple'])
    register_Ns3OlsrTwoHopNeighborTuple_methods(root_module, root_module['ns3::olsr::TwoHopNeighborTuple'])
    return

def register_Ns3OlsrHelper_methods(root_module, cls):
    ## olsr-helper.h: ns3::OlsrHelper::OlsrHelper() [constructor]
    cls.add_constructor([])
    ## olsr-helper.h: ns3::OlsrHelper::OlsrHelper(ns3::OlsrHelper const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::OlsrHelper const &', 'arg0')])
    ## olsr-helper.h: ns3::OlsrHelper * ns3::OlsrHelper::Copy() const [member function]
    cls.add_method('Copy', 
                   'ns3::OlsrHelper *', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-helper.h: void ns3::OlsrHelper::ExcludeInterface(ns3::Ptr<ns3::Node> node, uint32_t interface) [member function]
    cls.add_method('ExcludeInterface', 
                   'void', 
                   [param('ns3::Ptr< ns3::Node >', 'node'), param('uint32_t', 'interface')])
    ## olsr-helper.h: ns3::Ptr<ns3::Ipv4RoutingProtocol> ns3::OlsrHelper::Create(ns3::Ptr<ns3::Node> node) const [member function]
    cls.add_method('Create', 
                   'ns3::Ptr< ns3::Ipv4RoutingProtocol >', 
                   [param('ns3::Ptr< ns3::Node >', 'node')], 
                   is_const=True, is_virtual=True)
    ## olsr-helper.h: void ns3::OlsrHelper::Set(std::string name, ns3::AttributeValue const & value) [member function]
    cls.add_method('Set', 
                   'void', 
                   [param('std::string', 'name'), param('ns3::AttributeValue const &', 'value')])
    return

def register_Ns3OlsrState_methods(root_module, cls):
    ## olsr-state.h: ns3::OlsrState::OlsrState(ns3::OlsrState const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::OlsrState const &', 'arg0')])
    ## olsr-state.h: ns3::OlsrState::OlsrState() [constructor]
    cls.add_constructor([])
    ## olsr-state.h: void ns3::OlsrState::EraseAssociation(ns3::olsr::Association const & tuple) [member function]
    cls.add_method('EraseAssociation', 
                   'void', 
                   [param('ns3::olsr::Association const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseAssociationTuple(ns3::olsr::AssociationTuple const & tuple) [member function]
    cls.add_method('EraseAssociationTuple', 
                   'void', 
                   [param('ns3::olsr::AssociationTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseDuplicateTuple(ns3::olsr::DuplicateTuple const & tuple) [member function]
    cls.add_method('EraseDuplicateTuple', 
                   'void', 
                   [param('ns3::olsr::DuplicateTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseIfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & tuple) [member function]
    cls.add_method('EraseIfaceAssocTuple', 
                   'void', 
                   [param('ns3::olsr::IfaceAssocTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseLinkTuple(ns3::olsr::LinkTuple const & tuple) [member function]
    cls.add_method('EraseLinkTuple', 
                   'void', 
                   [param('ns3::olsr::LinkTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseMprSelectorTuple(ns3::olsr::MprSelectorTuple const & tuple) [member function]
    cls.add_method('EraseMprSelectorTuple', 
                   'void', 
                   [param('ns3::olsr::MprSelectorTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseMprSelectorTuples(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('EraseMprSelectorTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h: void ns3::OlsrState::EraseNeighborTuple(ns3::olsr::NeighborTuple const & neighborTuple) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::NeighborTuple const &', 'neighborTuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('EraseNeighborTuple', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h: void ns3::OlsrState::EraseOlderTopologyTuples(ns3::Ipv4Address const & lastAddr, uint16_t ansn) [member function]
    cls.add_method('EraseOlderTopologyTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'lastAddr'), param('uint16_t', 'ansn')])
    ## olsr-state.h: void ns3::OlsrState::EraseTopologyTuple(ns3::olsr::TopologyTuple const & tuple) [member function]
    cls.add_method('EraseTopologyTuple', 
                   'void', 
                   [param('ns3::olsr::TopologyTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseTwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & tuple) [member function]
    cls.add_method('EraseTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::TwoHopNeighborTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::EraseTwoHopNeighborTuples(ns3::Ipv4Address const & neighbor) [member function]
    cls.add_method('EraseTwoHopNeighborTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'neighbor')])
    ## olsr-state.h: void ns3::OlsrState::EraseTwoHopNeighborTuples(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('EraseTwoHopNeighborTuples', 
                   'void', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## olsr-state.h: ns3::olsr::AssociationTuple * ns3::OlsrState::FindAssociationTuple(ns3::Ipv4Address const & gatewayAddr, ns3::Ipv4Address const & networkAddr, ns3::Ipv4Mask const & netmask) [member function]
    cls.add_method('FindAssociationTuple', 
                   'ns3::olsr::AssociationTuple *', 
                   [param('ns3::Ipv4Address const &', 'gatewayAddr'), param('ns3::Ipv4Address const &', 'networkAddr'), param('ns3::Ipv4Mask const &', 'netmask')])
    ## olsr-state.h: ns3::olsr::DuplicateTuple * ns3::OlsrState::FindDuplicateTuple(ns3::Ipv4Address const & address, uint16_t sequenceNumber) [member function]
    cls.add_method('FindDuplicateTuple', 
                   'ns3::olsr::DuplicateTuple *', 
                   [param('ns3::Ipv4Address const &', 'address'), param('uint16_t', 'sequenceNumber')])
    ## olsr-state.h: ns3::olsr::IfaceAssocTuple * ns3::OlsrState::FindIfaceAssocTuple(ns3::Ipv4Address const & ifaceAddr) [member function]
    cls.add_method('FindIfaceAssocTuple', 
                   'ns3::olsr::IfaceAssocTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')])
    ## olsr-state.h: ns3::olsr::IfaceAssocTuple const * ns3::OlsrState::FindIfaceAssocTuple(ns3::Ipv4Address const & ifaceAddr) const [member function]
    cls.add_method('FindIfaceAssocTuple', 
                   'ns3::olsr::IfaceAssocTuple const *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::LinkTuple * ns3::OlsrState::FindLinkTuple(ns3::Ipv4Address const & ifaceAddr) [member function]
    cls.add_method('FindLinkTuple', 
                   'ns3::olsr::LinkTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr')])
    ## olsr-state.h: bool ns3::OlsrState::FindMprAddress(ns3::Ipv4Address const & address) [member function]
    cls.add_method('FindMprAddress', 
                   'bool', 
                   [param('ns3::Ipv4Address const &', 'address')])
    ## olsr-state.h: ns3::olsr::MprSelectorTuple * ns3::OlsrState::FindMprSelectorTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('FindMprSelectorTuple', 
                   'ns3::olsr::MprSelectorTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h: std::vector<ns3::Ipv4Address, std::allocator<ns3::Ipv4Address> > ns3::OlsrState::FindNeighborInterfaces(ns3::Ipv4Address const & neighborMainAddr) const [member function]
    cls.add_method('FindNeighborInterfaces', 
                   'std::vector< ns3::Ipv4Address >', 
                   [param('ns3::Ipv4Address const &', 'neighborMainAddr')], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::NeighborTuple * ns3::OlsrState::FindNeighborTuple(ns3::Ipv4Address const & mainAddr) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::olsr::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')])
    ## olsr-state.h: ns3::olsr::NeighborTuple * ns3::OlsrState::FindNeighborTuple(ns3::Ipv4Address const & mainAddr, uint8_t willingness) [member function]
    cls.add_method('FindNeighborTuple', 
                   'ns3::olsr::NeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr'), param('uint8_t', 'willingness')])
    ## olsr-state.h: ns3::olsr::TopologyTuple * ns3::OlsrState::FindNewerTopologyTuple(ns3::Ipv4Address const & lastAddr, uint16_t ansn) [member function]
    cls.add_method('FindNewerTopologyTuple', 
                   'ns3::olsr::TopologyTuple *', 
                   [param('ns3::Ipv4Address const &', 'lastAddr'), param('uint16_t', 'ansn')])
    ## olsr-state.h: ns3::olsr::LinkTuple * ns3::OlsrState::FindSymLinkTuple(ns3::Ipv4Address const & ifaceAddr, ns3::Time time) [member function]
    cls.add_method('FindSymLinkTuple', 
                   'ns3::olsr::LinkTuple *', 
                   [param('ns3::Ipv4Address const &', 'ifaceAddr'), param('ns3::Time', 'time')])
    ## olsr-state.h: ns3::olsr::NeighborTuple const * ns3::OlsrState::FindSymNeighborTuple(ns3::Ipv4Address const & mainAddr) const [member function]
    cls.add_method('FindSymNeighborTuple', 
                   'ns3::olsr::NeighborTuple const *', 
                   [param('ns3::Ipv4Address const &', 'mainAddr')], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::TopologyTuple * ns3::OlsrState::FindTopologyTuple(ns3::Ipv4Address const & destAddr, ns3::Ipv4Address const & lastAddr) [member function]
    cls.add_method('FindTopologyTuple', 
                   'ns3::olsr::TopologyTuple *', 
                   [param('ns3::Ipv4Address const &', 'destAddr'), param('ns3::Ipv4Address const &', 'lastAddr')])
    ## olsr-state.h: ns3::olsr::TwoHopNeighborTuple * ns3::OlsrState::FindTwoHopNeighborTuple(ns3::Ipv4Address const & neighbor, ns3::Ipv4Address const & twoHopNeighbor) [member function]
    cls.add_method('FindTwoHopNeighborTuple', 
                   'ns3::olsr::TwoHopNeighborTuple *', 
                   [param('ns3::Ipv4Address const &', 'neighbor'), param('ns3::Ipv4Address const &', 'twoHopNeighbor')])
    ## olsr-state.h: ns3::olsr::AssociationSet const & ns3::OlsrState::GetAssociationSet() const [member function]
    cls.add_method('GetAssociationSet', 
                   'ns3::olsr::AssociationSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::Associations const & ns3::OlsrState::GetAssociations() const [member function]
    cls.add_method('GetAssociations', 
                   'ns3::olsr::Associations const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::IfaceAssocSet const & ns3::OlsrState::GetIfaceAssocSet() const [member function]
    cls.add_method('GetIfaceAssocSet', 
                   'ns3::olsr::IfaceAssocSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::IfaceAssocSet & ns3::OlsrState::GetIfaceAssocSetMutable() [member function]
    cls.add_method('GetIfaceAssocSetMutable', 
                   'ns3::olsr::IfaceAssocSet &', 
                   [])
    ## olsr-state.h: ns3::olsr::LinkSet const & ns3::OlsrState::GetLinks() const [member function]
    cls.add_method('GetLinks', 
                   'ns3::olsr::LinkSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::MprSelectorSet const & ns3::OlsrState::GetMprSelectors() const [member function]
    cls.add_method('GetMprSelectors', 
                   'ns3::olsr::MprSelectorSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::MprSet ns3::OlsrState::GetMprSet() const [member function]
    cls.add_method('GetMprSet', 
                   'ns3::olsr::MprSet', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::NeighborSet const & ns3::OlsrState::GetNeighbors() const [member function]
    cls.add_method('GetNeighbors', 
                   'ns3::olsr::NeighborSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::NeighborSet & ns3::OlsrState::GetNeighbors() [member function]
    cls.add_method('GetNeighbors', 
                   'ns3::olsr::NeighborSet &', 
                   [])
    ## olsr-state.h: ns3::olsr::TopologySet const & ns3::OlsrState::GetTopologySet() const [member function]
    cls.add_method('GetTopologySet', 
                   'ns3::olsr::TopologySet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::TwoHopNeighborSet const & ns3::OlsrState::GetTwoHopNeighbors() const [member function]
    cls.add_method('GetTwoHopNeighbors', 
                   'ns3::olsr::TwoHopNeighborSet const &', 
                   [], 
                   is_const=True)
    ## olsr-state.h: ns3::olsr::TwoHopNeighborSet & ns3::OlsrState::GetTwoHopNeighbors() [member function]
    cls.add_method('GetTwoHopNeighbors', 
                   'ns3::olsr::TwoHopNeighborSet &', 
                   [])
    ## olsr-state.h: void ns3::OlsrState::InsertAssociation(ns3::olsr::Association const & tuple) [member function]
    cls.add_method('InsertAssociation', 
                   'void', 
                   [param('ns3::olsr::Association const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertAssociationTuple(ns3::olsr::AssociationTuple const & tuple) [member function]
    cls.add_method('InsertAssociationTuple', 
                   'void', 
                   [param('ns3::olsr::AssociationTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertDuplicateTuple(ns3::olsr::DuplicateTuple const & tuple) [member function]
    cls.add_method('InsertDuplicateTuple', 
                   'void', 
                   [param('ns3::olsr::DuplicateTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertIfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & tuple) [member function]
    cls.add_method('InsertIfaceAssocTuple', 
                   'void', 
                   [param('ns3::olsr::IfaceAssocTuple const &', 'tuple')])
    ## olsr-state.h: ns3::olsr::LinkTuple & ns3::OlsrState::InsertLinkTuple(ns3::olsr::LinkTuple const & tuple) [member function]
    cls.add_method('InsertLinkTuple', 
                   'ns3::olsr::LinkTuple &', 
                   [param('ns3::olsr::LinkTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertMprSelectorTuple(ns3::olsr::MprSelectorTuple const & tuple) [member function]
    cls.add_method('InsertMprSelectorTuple', 
                   'void', 
                   [param('ns3::olsr::MprSelectorTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertNeighborTuple(ns3::olsr::NeighborTuple const & tuple) [member function]
    cls.add_method('InsertNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::NeighborTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertTopologyTuple(ns3::olsr::TopologyTuple const & tuple) [member function]
    cls.add_method('InsertTopologyTuple', 
                   'void', 
                   [param('ns3::olsr::TopologyTuple const &', 'tuple')])
    ## olsr-state.h: void ns3::OlsrState::InsertTwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & tuple) [member function]
    cls.add_method('InsertTwoHopNeighborTuple', 
                   'void', 
                   [param('ns3::olsr::TwoHopNeighborTuple const &', 'tuple')])
    ## olsr-state.h: std::string ns3::OlsrState::PrintMprSelectorSet() const [member function]
    cls.add_method('PrintMprSelectorSet', 
                   'std::string', 
                   [], 
                   is_const=True)
    ## olsr-state.h: void ns3::OlsrState::SetMprSet(ns3::olsr::MprSet mprSet) [member function]
    cls.add_method('SetMprSet', 
                   'void', 
                   [param('ns3::olsr::MprSet', 'mprSet')])
    return

def register_Ns3OlsrAssociation_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::Association::Association() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::Association::Association(ns3::olsr::Association const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::Association const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::Association::netmask [variable]
    cls.add_instance_attribute('netmask', 'ns3::Ipv4Mask', is_const=False)
    ## olsr-repositories.h: ns3::olsr::Association::networkAddr [variable]
    cls.add_instance_attribute('networkAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrAssociationTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::AssociationTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::AssociationTuple(ns3::olsr::AssociationTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::AssociationTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::gatewayAddr [variable]
    cls.add_instance_attribute('gatewayAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::netmask [variable]
    cls.add_instance_attribute('netmask', 'ns3::Ipv4Mask', is_const=False)
    ## olsr-repositories.h: ns3::olsr::AssociationTuple::networkAddr [variable]
    cls.add_instance_attribute('networkAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrDuplicateTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::DuplicateTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::DuplicateTuple(ns3::olsr::DuplicateTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::DuplicateTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::address [variable]
    cls.add_instance_attribute('address', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::ifaceList [variable]
    cls.add_instance_attribute('ifaceList', 'std::vector< ns3::Ipv4Address >', is_const=False)
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::retransmitted [variable]
    cls.add_instance_attribute('retransmitted', 'bool', is_const=False)
    ## olsr-repositories.h: ns3::olsr::DuplicateTuple::sequenceNumber [variable]
    cls.add_instance_attribute('sequenceNumber', 'uint16_t', is_const=False)
    return

def register_Ns3OlsrIfaceAssocTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple::IfaceAssocTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple::IfaceAssocTuple(ns3::olsr::IfaceAssocTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::IfaceAssocTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple::ifaceAddr [variable]
    cls.add_instance_attribute('ifaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple::mainAddr [variable]
    cls.add_instance_attribute('mainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::IfaceAssocTuple::time [variable]
    cls.add_instance_attribute('time', 'ns3::Time', is_const=False)
    return

def register_Ns3OlsrLinkTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::LinkTuple::LinkTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::LinkTuple::LinkTuple(ns3::olsr::LinkTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::LinkTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::LinkTuple::asymTime [variable]
    cls.add_instance_attribute('asymTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::LinkTuple::localIfaceAddr [variable]
    cls.add_instance_attribute('localIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::LinkTuple::neighborIfaceAddr [variable]
    cls.add_instance_attribute('neighborIfaceAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::LinkTuple::symTime [variable]
    cls.add_instance_attribute('symTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::LinkTuple::time [variable]
    cls.add_instance_attribute('time', 'ns3::Time', is_const=False)
    return

def register_Ns3OlsrMessageHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## olsr-header.h: ns3::olsr::MessageHeader::MessageHeader(ns3::olsr::MessageHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader const &', 'arg0')])
    ## olsr-header.h: ns3::olsr::MessageHeader::MessageHeader() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello & ns3::olsr::MessageHeader::GetHello() [member function]
    cls.add_method('GetHello', 
                   'ns3::olsr::MessageHeader::Hello &', 
                   [])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello const & ns3::olsr::MessageHeader::GetHello() const [member function]
    cls.add_method('GetHello', 
                   'ns3::olsr::MessageHeader::Hello const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna & ns3::olsr::MessageHeader::GetHna() [member function]
    cls.add_method('GetHna', 
                   'ns3::olsr::MessageHeader::Hna &', 
                   [])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna const & ns3::olsr::MessageHeader::GetHna() const [member function]
    cls.add_method('GetHna', 
                   'ns3::olsr::MessageHeader::Hna const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint8_t ns3::olsr::MessageHeader::GetHopCount() const [member function]
    cls.add_method('GetHopCount', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: ns3::TypeId ns3::olsr::MessageHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: uint16_t ns3::olsr::MessageHeader::GetMessageSequenceNumber() const [member function]
    cls.add_method('GetMessageSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::MessageType ns3::olsr::MessageHeader::GetMessageType() const [member function]
    cls.add_method('GetMessageType', 
                   'ns3::olsr::MessageHeader::MessageType', 
                   [], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid & ns3::olsr::MessageHeader::GetMid() [member function]
    cls.add_method('GetMid', 
                   'ns3::olsr::MessageHeader::Mid &', 
                   [])
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid const & ns3::olsr::MessageHeader::GetMid() const [member function]
    cls.add_method('GetMid', 
                   'ns3::olsr::MessageHeader::Mid const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h: ns3::Ipv4Address ns3::olsr::MessageHeader::GetOriginatorAddress() const [member function]
    cls.add_method('GetOriginatorAddress', 
                   'ns3::Ipv4Address', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc & ns3::olsr::MessageHeader::GetTc() [member function]
    cls.add_method('GetTc', 
                   'ns3::olsr::MessageHeader::Tc &', 
                   [])
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc const & ns3::olsr::MessageHeader::GetTc() const [member function]
    cls.add_method('GetTc', 
                   'ns3::olsr::MessageHeader::Tc const &', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint8_t ns3::olsr::MessageHeader::GetTimeToLive() const [member function]
    cls.add_method('GetTimeToLive', 
                   'uint8_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: static ns3::TypeId ns3::olsr::MessageHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-header.h: ns3::Time ns3::olsr::MessageHeader::GetVTime() const [member function]
    cls.add_method('GetVTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetHopCount(uint8_t hopCount) [member function]
    cls.add_method('SetHopCount', 
                   'void', 
                   [param('uint8_t', 'hopCount')])
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetMessageSequenceNumber(uint16_t messageSequenceNumber) [member function]
    cls.add_method('SetMessageSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'messageSequenceNumber')])
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetMessageType(ns3::olsr::MessageHeader::MessageType messageType) [member function]
    cls.add_method('SetMessageType', 
                   'void', 
                   [param('ns3::olsr::MessageHeader::MessageType', 'messageType')])
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetOriginatorAddress(ns3::Ipv4Address originatorAddress) [member function]
    cls.add_method('SetOriginatorAddress', 
                   'void', 
                   [param('ns3::Ipv4Address', 'originatorAddress')])
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetTimeToLive(uint8_t timeToLive) [member function]
    cls.add_method('SetTimeToLive', 
                   'void', 
                   [param('uint8_t', 'timeToLive')])
    ## olsr-header.h: void ns3::olsr::MessageHeader::SetVTime(ns3::Time time) [member function]
    cls.add_method('SetVTime', 
                   'void', 
                   [param('ns3::Time', 'time')])
    return

def register_Ns3OlsrMessageHeaderHello_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::Hello() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::Hello(ns3::olsr::MessageHeader::Hello const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hello const &', 'arg0')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Hello::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h: ns3::Time ns3::olsr::MessageHeader::Hello::GetHTime() const [member function]
    cls.add_method('GetHTime', 
                   'ns3::Time', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Hello::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Hello::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Hello::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Hello::SetHTime(ns3::Time time) [member function]
    cls.add_method('SetHTime', 
                   'void', 
                   [param('ns3::Time', 'time')])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::hTime [variable]
    cls.add_instance_attribute('hTime', 'uint8_t', is_const=False)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::linkMessages [variable]
    cls.add_instance_attribute('linkMessages', 'std::vector< ns3::olsr::MessageHeader::Hello::LinkMessage >', is_const=False)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::willingness [variable]
    cls.add_instance_attribute('willingness', 'uint8_t', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHelloLinkMessage_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::LinkMessage::LinkMessage() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::LinkMessage::LinkMessage(ns3::olsr::MessageHeader::Hello::LinkMessage const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hello::LinkMessage const &', 'arg0')])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::LinkMessage::linkCode [variable]
    cls.add_instance_attribute('linkCode', 'uint8_t', is_const=False)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hello::LinkMessage::neighborInterfaceAddresses [variable]
    cls.add_instance_attribute('neighborInterfaceAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHna_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Hna() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Hna(ns3::olsr::MessageHeader::Hna const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hna const &', 'arg0')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Hna::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Hna::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Hna::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Hna::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::associations [variable]
    cls.add_instance_attribute('associations', 'std::vector< ns3::olsr::MessageHeader::Hna::Association >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderHnaAssociation_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Association::Association() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Association::Association(ns3::olsr::MessageHeader::Hna::Association const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Hna::Association const &', 'arg0')])
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Association::address [variable]
    cls.add_instance_attribute('address', 'ns3::Ipv4Address', is_const=False)
    ## olsr-header.h: ns3::olsr::MessageHeader::Hna::Association::mask [variable]
    cls.add_instance_attribute('mask', 'ns3::Ipv4Mask', is_const=False)
    return

def register_Ns3OlsrMessageHeaderMid_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid::Mid() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid::Mid(ns3::olsr::MessageHeader::Mid const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Mid const &', 'arg0')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Mid::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Mid::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Mid::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Mid::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Mid::interfaceAddresses [variable]
    cls.add_instance_attribute('interfaceAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMessageHeaderTc_methods(root_module, cls):
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc::Tc() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc::Tc(ns3::olsr::MessageHeader::Tc const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MessageHeader::Tc const &', 'arg0')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Tc::Deserialize(ns3::Buffer::Iterator start, uint32_t messageSize) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start'), param('uint32_t', 'messageSize')])
    ## olsr-header.h: uint32_t ns3::olsr::MessageHeader::Tc::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Tc::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True)
    ## olsr-header.h: void ns3::olsr::MessageHeader::Tc::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True)
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc::ansn [variable]
    cls.add_instance_attribute('ansn', 'uint16_t', is_const=False)
    ## olsr-header.h: ns3::olsr::MessageHeader::Tc::neighborAddresses [variable]
    cls.add_instance_attribute('neighborAddresses', 'std::vector< ns3::Ipv4Address >', is_const=False)
    return

def register_Ns3OlsrMprSelectorTuple_methods(root_module, cls):
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::MprSelectorTuple::MprSelectorTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::MprSelectorTuple::MprSelectorTuple(ns3::olsr::MprSelectorTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::MprSelectorTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::MprSelectorTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::MprSelectorTuple::mainAddr [variable]
    cls.add_instance_attribute('mainAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrNeighborTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::NeighborTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::NeighborTuple(ns3::olsr::NeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::NeighborTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::neighborMainAddr [variable]
    cls.add_instance_attribute('neighborMainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::status [variable]
    cls.add_instance_attribute('status', 'ns3::olsr::NeighborTuple::Status', is_const=False)
    ## olsr-repositories.h: ns3::olsr::NeighborTuple::willingness [variable]
    cls.add_instance_attribute('willingness', 'uint8_t', is_const=False)
    return

def register_Ns3OlsrPacketHeader_methods(root_module, cls):
    cls.add_output_stream_operator()
    ## olsr-header.h: ns3::olsr::PacketHeader::PacketHeader(ns3::olsr::PacketHeader const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::PacketHeader const &', 'arg0')])
    ## olsr-header.h: ns3::olsr::PacketHeader::PacketHeader() [constructor]
    cls.add_constructor([])
    ## olsr-header.h: uint32_t ns3::olsr::PacketHeader::Deserialize(ns3::Buffer::Iterator start) [member function]
    cls.add_method('Deserialize', 
                   'uint32_t', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_virtual=True)
    ## olsr-header.h: ns3::TypeId ns3::olsr::PacketHeader::GetInstanceTypeId() const [member function]
    cls.add_method('GetInstanceTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: uint16_t ns3::olsr::PacketHeader::GetPacketLength() const [member function]
    cls.add_method('GetPacketLength', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint16_t ns3::olsr::PacketHeader::GetPacketSequenceNumber() const [member function]
    cls.add_method('GetPacketSequenceNumber', 
                   'uint16_t', 
                   [], 
                   is_const=True)
    ## olsr-header.h: uint32_t ns3::olsr::PacketHeader::GetSerializedSize() const [member function]
    cls.add_method('GetSerializedSize', 
                   'uint32_t', 
                   [], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: static ns3::TypeId ns3::olsr::PacketHeader::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-header.h: void ns3::olsr::PacketHeader::Print(std::ostream & os) const [member function]
    cls.add_method('Print', 
                   'void', 
                   [param('std::ostream &', 'os')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: void ns3::olsr::PacketHeader::Serialize(ns3::Buffer::Iterator start) const [member function]
    cls.add_method('Serialize', 
                   'void', 
                   [param('ns3::Buffer::Iterator', 'start')], 
                   is_const=True, is_virtual=True)
    ## olsr-header.h: void ns3::olsr::PacketHeader::SetPacketLength(uint16_t length) [member function]
    cls.add_method('SetPacketLength', 
                   'void', 
                   [param('uint16_t', 'length')])
    ## olsr-header.h: void ns3::olsr::PacketHeader::SetPacketSequenceNumber(uint16_t seqnum) [member function]
    cls.add_method('SetPacketSequenceNumber', 
                   'void', 
                   [param('uint16_t', 'seqnum')])
    return

def register_Ns3OlsrRoutingProtocol_methods(root_module, cls):
    ## olsr-routing-protocol.h: ns3::olsr::RoutingProtocol::RoutingProtocol(ns3::olsr::RoutingProtocol const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::RoutingProtocol const &', 'arg0')])
    ## olsr-routing-protocol.h: ns3::olsr::RoutingProtocol::RoutingProtocol() [constructor]
    cls.add_constructor([])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::AddHostNetworkAssociation(ns3::Ipv4Address networkAddr, ns3::Ipv4Mask netmask) [member function]
    cls.add_method('AddHostNetworkAssociation', 
                   'void', 
                   [param('ns3::Ipv4Address', 'networkAddr'), param('ns3::Ipv4Mask', 'netmask')])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::Dump() [member function]
    cls.add_method('Dump', 
                   'void', 
                   [])
    ## olsr-routing-protocol.h: std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > ns3::olsr::RoutingProtocol::GetInterfaceExclusions() const [member function]
    cls.add_method('GetInterfaceExclusions', 
                   'std::set< unsigned int >', 
                   [], 
                   is_const=True)
    ## olsr-routing-protocol.h: std::vector<ns3::olsr::RoutingTableEntry,std::allocator<ns3::olsr::RoutingTableEntry> > ns3::olsr::RoutingProtocol::GetRoutingTableEntries() const [member function]
    cls.add_method('GetRoutingTableEntries', 
                   'std::vector< ns3::olsr::RoutingTableEntry >', 
                   [], 
                   is_const=True)
    ## olsr-routing-protocol.h: static ns3::TypeId ns3::olsr::RoutingProtocol::GetTypeId() [member function]
    cls.add_method('GetTypeId', 
                   'ns3::TypeId', 
                   [], 
                   is_static=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::RemoveHostNetworkAssociation(ns3::Ipv4Address networkAddr, ns3::Ipv4Mask netmask) [member function]
    cls.add_method('RemoveHostNetworkAssociation', 
                   'void', 
                   [param('ns3::Ipv4Address', 'networkAddr'), param('ns3::Ipv4Mask', 'netmask')])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::SetInterfaceExclusions(std::set<unsigned int, std::less<unsigned int>, std::allocator<unsigned int> > exceptions) [member function]
    cls.add_method('SetInterfaceExclusions', 
                   'void', 
                   [param('std::set< unsigned int >', 'exceptions')])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::SetMainInterface(uint32_t interface) [member function]
    cls.add_method('SetMainInterface', 
                   'void', 
                   [param('uint32_t', 'interface')])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::SetRoutingTableAssociation(ns3::Ptr<ns3::Ipv4StaticRouting> routingTable) [member function]
    cls.add_method('SetRoutingTableAssociation', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4StaticRouting >', 'routingTable')])
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::DoStart() [member function]
    cls.add_method('DoStart', 
                   'void', 
                   [], 
                   visibility='protected', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::DoDispose() [member function]
    cls.add_method('DoDispose', 
                   'void', 
                   [], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::NotifyAddAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyAddAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::NotifyInterfaceDown(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceDown', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::NotifyInterfaceUp(uint32_t interface) [member function]
    cls.add_method('NotifyInterfaceUp', 
                   'void', 
                   [param('uint32_t', 'interface')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::NotifyRemoveAddress(uint32_t interface, ns3::Ipv4InterfaceAddress address) [member function]
    cls.add_method('NotifyRemoveAddress', 
                   'void', 
                   [param('uint32_t', 'interface'), param('ns3::Ipv4InterfaceAddress', 'address')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::PrintRoutingTable(ns3::Ptr<ns3::OutputStreamWrapper> stream) const [member function]
    cls.add_method('PrintRoutingTable', 
                   'void', 
                   [param('ns3::Ptr< ns3::OutputStreamWrapper >', 'stream')], 
                   is_const=True, visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: bool ns3::olsr::RoutingProtocol::RouteInput(ns3::Ptr<ns3::Packet const> p, ns3::Ipv4Header const & header, ns3::Ptr<const ns3::NetDevice> idev, ns3::Callback<void, ns3::Ptr<ns3::Ipv4Route>, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ucb, ns3::Callback<void,ns3::Ptr<ns3::Ipv4MulticastRoute>,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> mcb, ns3::Callback<void,ns3::Ptr<const ns3::Packet>,const ns3::Ipv4Header&,unsigned int,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty,ns3::empty> lcb, ns3::Callback<void, ns3::Ptr<ns3::Packet const>, ns3::Ipv4Header const&, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty> ecb) [member function]
    cls.add_method('RouteInput', 
                   'bool', 
                   [param('ns3::Ptr< ns3::Packet const >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice const >', 'idev'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4Route >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ucb'), param('ns3::Callback< void, ns3::Ptr< ns3::Ipv4MulticastRoute >, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'mcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, unsigned int, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'lcb'), param('ns3::Callback< void, ns3::Ptr< ns3::Packet const >, ns3::Ipv4Header const &, ns3::Socket::SocketErrno, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty, ns3::empty >', 'ecb')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: ns3::Ptr<ns3::Ipv4Route> ns3::olsr::RoutingProtocol::RouteOutput(ns3::Ptr<ns3::Packet> p, ns3::Ipv4Header const & header, ns3::Ptr<ns3::NetDevice> oif, ns3::Socket::SocketErrno & sockerr) [member function]
    cls.add_method('RouteOutput', 
                   'ns3::Ptr< ns3::Ipv4Route >', 
                   [param('ns3::Ptr< ns3::Packet >', 'p'), param('ns3::Ipv4Header const &', 'header'), param('ns3::Ptr< ns3::NetDevice >', 'oif'), param('ns3::Socket::SocketErrno &', 'sockerr')], 
                   visibility='private', is_virtual=True)
    ## olsr-routing-protocol.h: void ns3::olsr::RoutingProtocol::SetIpv4(ns3::Ptr<ns3::Ipv4> ipv4) [member function]
    cls.add_method('SetIpv4', 
                   'void', 
                   [param('ns3::Ptr< ns3::Ipv4 >', 'ipv4')], 
                   visibility='private', is_virtual=True)
    return

def register_Ns3OlsrRoutingTableEntry_methods(root_module, cls):
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::RoutingTableEntry(ns3::olsr::RoutingTableEntry const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::RoutingTableEntry const &', 'arg0')])
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::RoutingTableEntry() [constructor]
    cls.add_constructor([])
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::destAddr [variable]
    cls.add_instance_attribute('destAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::distance [variable]
    cls.add_instance_attribute('distance', 'uint32_t', is_const=False)
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::interface [variable]
    cls.add_instance_attribute('interface', 'uint32_t', is_const=False)
    ## olsr-routing-protocol.h: ns3::olsr::RoutingTableEntry::nextAddr [variable]
    cls.add_instance_attribute('nextAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_Ns3OlsrTopologyTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::TopologyTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::TopologyTuple(ns3::olsr::TopologyTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::TopologyTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::destAddr [variable]
    cls.add_instance_attribute('destAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::lastAddr [variable]
    cls.add_instance_attribute('lastAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::TopologyTuple::sequenceNumber [variable]
    cls.add_instance_attribute('sequenceNumber', 'uint16_t', is_const=False)
    return

def register_Ns3OlsrTwoHopNeighborTuple_methods(root_module, cls):
    cls.add_output_stream_operator()
    cls.add_binary_comparison_operator('==')
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple::TwoHopNeighborTuple() [constructor]
    cls.add_constructor([])
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple::TwoHopNeighborTuple(ns3::olsr::TwoHopNeighborTuple const & arg0) [copy constructor]
    cls.add_constructor([param('ns3::olsr::TwoHopNeighborTuple const &', 'arg0')])
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple::expirationTime [variable]
    cls.add_instance_attribute('expirationTime', 'ns3::Time', is_const=False)
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple::neighborMainAddr [variable]
    cls.add_instance_attribute('neighborMainAddr', 'ns3::Ipv4Address', is_const=False)
    ## olsr-repositories.h: ns3::olsr::TwoHopNeighborTuple::twoHopNeighborAddr [variable]
    cls.add_instance_attribute('twoHopNeighborAddr', 'ns3::Ipv4Address', is_const=False)
    return

def register_functions(root_module):
    module = root_module
    register_functions_ns3_Config(module.get_submodule('Config'), root_module)
    register_functions_ns3_FatalImpl(module.get_submodule('FatalImpl'), root_module)
    register_functions_ns3_addressUtils(module.get_submodule('addressUtils'), root_module)
    register_functions_ns3_aodv(module.get_submodule('aodv'), root_module)
    register_functions_ns3_dot11s(module.get_submodule('dot11s'), root_module)
    register_functions_ns3_dsdv(module.get_submodule('dsdv'), root_module)
    register_functions_ns3_flame(module.get_submodule('flame'), root_module)
    register_functions_ns3_internal(module.get_submodule('internal'), root_module)
    register_functions_ns3_olsr(module.get_submodule('olsr'), root_module)
    return

def register_functions_ns3_Config(module, root_module):
    return

def register_functions_ns3_FatalImpl(module, root_module):
    return

def register_functions_ns3_addressUtils(module, root_module):
    return

def register_functions_ns3_aodv(module, root_module):
    return

def register_functions_ns3_dot11s(module, root_module):
    return

def register_functions_ns3_dsdv(module, root_module):
    return

def register_functions_ns3_flame(module, root_module):
    return

def register_functions_ns3_internal(module, root_module):
    return

def register_functions_ns3_olsr(module, root_module):
    ## olsr-header.h: extern double ns3::olsr::EmfToSeconds(uint8_t emf) [free function]
    module.add_function('EmfToSeconds', 
                        'double', 
                        [param('uint8_t', 'emf')])
    ## olsr-header.h: extern uint8_t ns3::olsr::SecondsToEmf(double seconds) [free function]
    module.add_function('SecondsToEmf', 
                        'uint8_t', 
                        [param('double', 'seconds')])
    return

