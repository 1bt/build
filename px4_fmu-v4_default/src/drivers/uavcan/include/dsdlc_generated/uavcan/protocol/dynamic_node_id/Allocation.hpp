/*
 * UAVCAN data structure definition for libuavcan.
 *
 * Autogenerated, do not edit.
 *
 * Source file: /home/src/Firmware/src/drivers/uavcan/libuavcan/dsdl/uavcan/protocol/dynamic_node_id/1.Allocation.uavcan
 */

#ifndef UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_HPP_INCLUDED
#define UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_HPP_INCLUDED

#include <uavcan/build_config.hpp>
#include <uavcan/node/global_data_type_registry.hpp>
#include <uavcan/marshal/types.hpp>

/******************************* Source text **********************************
#
# This message is used for dynamic Node ID allocation.
#
# When a node needs to request a node ID dynamically, it will transmit an anonymous message transfer of this type.
# In order to reduce probability of CAN ID collisions when multiple nodes are publishing this request, the CAN ID
# field of anonymous message transfer includes a Discriminator, which is a special field that has to be filled with
# random data by the transmitting node. Since Discriminator collisions are likely to happen (probability approx.
# 0.006%), nodes that are requesting dynamic allocations need to be able to handle them correctly. Hence, a collision
# resolution protocol is defined (alike CSMA/CD). The collision resolution protocol is based on two randomized
# transmission intervals:
#
# - Request period - Trequest.
# - Follow up delay - Tfollowup.
#
# Recommended randomization ranges for these intervals are documented in the constants of this message type (see below).
# Random intervals must be chosen anew per transmission, whereas the Discriminator value is allowed to stay constant
# per node.
#
# In the below description the following terms are used:
# - Allocator - the node that serves allocation requests.
# - Allocatee - the node that requests an allocation from the Allocator.
#
# The response timeout is not explicitly defined for this protocol, as the Allocatee will request the allocation
# Trequest units of time later again, unless the allocation has been granted. Despite this, the implementation can
# consider the value of FOLLOWUP_TIMEOUT_MS as an allocation timeout, if necessary.
#
# On the allocatee's side the protocol is defined through the following set of rules:
#
# Rule A. On initialization:
# 1. The allocatee subscribes to this message.
# 2. The allocatee starts the Request Timer with a random interval of Trequest.
#
# Rule B. On expiration of Request Timer:
# 1. Request Timer restarts with a random interval of Trequest.
# 2. The allocatee broadcasts a first-stage Allocation request message, where the fields are assigned following values:
#    node_id                 - preferred node ID, or zero if the allocatee doesn't have any preference
#    first_part_of_unique_id - true
#    unique_id               - first MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST bytes of unique ID
#
# Rule C. On any Allocation message, even if other rules also match:
# 1. Request Timer restarts with a random interval of Trequest.
#
# Rule D. On an Allocation message WHERE (source node ID is non-anonymous) AND (allocatee's unique ID starts with the
# bytes available in the field unique_id) AND (unique_id is less than 16 bytes long):
# 1. The allocatee waits for Tfollowup units of time, while listening for other Allocation messages. If an Allocation
#    message is received during this time, the execution of this rule will be terminated. Also see rule C.
# 2. The allocatee broadcasts a second-stage Allocation request message, where the fields are assigned following values:
#    node_id                 - same value as in the first-stage
#    first_part_of_unique_id - false
#    unique_id               - at most MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST bytes of local unique ID with an offset
#                              equal to number of bytes in the received unique ID
#
# Rule E. On an Allocation message WHERE (source node ID is non-anonymous) AND (unique_id fully matches allocatee's
# unique ID) AND (node_id in the received message is not zero):
# 1. Request Timer stops.
# 2. The allocatee initializes its node_id with the received value.
# 3. The allocatee terminates subscription to Allocation messages.
# 4. Exit.
#

#
# Recommended randomization range for request period.
#
# These definitions have an advisory status; it is OK to pick higher values for both bounds, as it won't affect
# protocol compatibility. In fact, it is advised to pick higher values if the target application is not concerned
# about the time it will spend on completing the dynamic node ID allocation procedure, as it will reduce
# interference with other nodes, possibly of higher importance.
#
# The lower bound shall not be lower than FOLLOWUP_TIMEOUT_MS, otherwise the request may conflict with a followup.
#
uint16 MAX_REQUEST_PERIOD_MS = 1000     # It is OK to exceed this value
uint16 MIN_REQUEST_PERIOD_MS = 600      # It is OK to exceed this value

#
# Recommended randomization range for followup delay.
# The upper bound shall not exceed FOLLOWUP_TIMEOUT_MS, because the allocator will reset the state on its end.
#
uint16 MAX_FOLLOWUP_DELAY_MS = 400
uint16 MIN_FOLLOWUP_DELAY_MS = 0        # Defined only for regularity; will always be zero.

#
# Allocator will reset its state if there was no follow-up request in this amount of time.
#
uint16 FOLLOWUP_TIMEOUT_MS = 500

#
# Any request message can accommodate no more than this number of bytes of unique ID.
# This limitation is needed to ensure that all request transfers are single-frame.
# This limitation does not apply to CAN FD transport.
#
uint8 MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST = 6

#
# When requesting an allocation, set the field 'node_id' to this value if there's no preference.
#
uint7 ANY_NODE_ID = 0

#
# If transfer is anonymous, this is the preferred ID.
# If transfer is non-anonymous, this is allocated ID.
#
# If the allocatee does not have any preference, this value must be set to zero. In this case, the allocator
# must choose the highest unused node ID value for this allocation (except 126 and 127, that are reserved for
# network maintenance tools). E.g., if the allocation table is empty and the node has requested an allocation
# without any preference, the allocator will grant the node ID 125.
#
# If the preferred node ID is not zero, the allocator will traverse the allocation table starting from the
# preferred node ID upward, until a free node ID is found. If a free node ID could not be found, the
# allocator will restart the search from the preferred node ID downward, until a free node ID is found.
#
# In pseudocode:
#   int findFreeNodeID(const int preferred)
#   {
#       // Search up
#       int candidate = (preferred > 0) ? preferred : 125;
#       while (candidate <= 125)
#       {
#           if (!isOccupied(candidate))
#               return candidate;
#           candidate++;
#       }
#       // Search down
#       candidate = (preferred > 0) ? preferred : 125;
#       while (candidate > 0)
#       {
#           if (!isOccupied(candidate))
#               return candidate;
#           candidate--;
#       }
#       // Not found
#       return -1;
#   }
#
uint7 node_id

#
# If transfer is anonymous, this field indicates first-stage request.
# If transfer is non-anonymous, this field should be assigned zero and ignored.
#
bool first_part_of_unique_id

#
# If transfer is anonymous, this array must not contain more than MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST items.
# Note that array is tail-optimized, i.e. it will not be prepended with length field.
#
uint8[<=16] unique_id
******************************************************************************/

/********************* DSDL signature source definition ***********************
uavcan.protocol.dynamic_node_id.Allocation
saturated uint7 node_id
saturated bool first_part_of_unique_id
saturated uint8[<=16] unique_id
******************************************************************************/

#undef node_id
#undef first_part_of_unique_id
#undef unique_id
#undef MAX_REQUEST_PERIOD_MS
#undef MIN_REQUEST_PERIOD_MS
#undef MAX_FOLLOWUP_DELAY_MS
#undef MIN_FOLLOWUP_DELAY_MS
#undef FOLLOWUP_TIMEOUT_MS
#undef MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST
#undef ANY_NODE_ID

namespace uavcan
{
namespace protocol
{
namespace dynamic_node_id
{

template <int _tmpl>
struct UAVCAN_EXPORT Allocation_
{
    typedef const Allocation_<_tmpl>& ParameterType;
    typedef Allocation_<_tmpl>& ReferenceType;

    struct ConstantTypes
    {
        typedef ::uavcan::IntegerSpec< 16, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > MAX_REQUEST_PERIOD_MS;
        typedef ::uavcan::IntegerSpec< 16, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > MIN_REQUEST_PERIOD_MS;
        typedef ::uavcan::IntegerSpec< 16, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > MAX_FOLLOWUP_DELAY_MS;
        typedef ::uavcan::IntegerSpec< 16, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > MIN_FOLLOWUP_DELAY_MS;
        typedef ::uavcan::IntegerSpec< 16, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > FOLLOWUP_TIMEOUT_MS;
        typedef ::uavcan::IntegerSpec< 8, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST;
        typedef ::uavcan::IntegerSpec< 7, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > ANY_NODE_ID;
    };

    struct FieldTypes
    {
        typedef ::uavcan::IntegerSpec< 7, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > node_id;
        typedef ::uavcan::IntegerSpec< 1, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate > first_part_of_unique_id;
        typedef ::uavcan::Array< ::uavcan::IntegerSpec< 8, ::uavcan::SignednessUnsigned, ::uavcan::CastModeSaturate >, ::uavcan::ArrayModeDynamic, 16 > unique_id;
    };

    enum
    {
        MinBitLen
            = FieldTypes::node_id::MinBitLen
            + FieldTypes::first_part_of_unique_id::MinBitLen
            + FieldTypes::unique_id::MinBitLen
    };

    enum
    {
        MaxBitLen
            = FieldTypes::node_id::MaxBitLen
            + FieldTypes::first_part_of_unique_id::MaxBitLen
            + FieldTypes::unique_id::MaxBitLen
    };

    // Constants
    static const typename ::uavcan::StorageType< typename ConstantTypes::MAX_REQUEST_PERIOD_MS >::Type MAX_REQUEST_PERIOD_MS; // 1000
    static const typename ::uavcan::StorageType< typename ConstantTypes::MIN_REQUEST_PERIOD_MS >::Type MIN_REQUEST_PERIOD_MS; // 600
    static const typename ::uavcan::StorageType< typename ConstantTypes::MAX_FOLLOWUP_DELAY_MS >::Type MAX_FOLLOWUP_DELAY_MS; // 400
    static const typename ::uavcan::StorageType< typename ConstantTypes::MIN_FOLLOWUP_DELAY_MS >::Type MIN_FOLLOWUP_DELAY_MS; // 0
    static const typename ::uavcan::StorageType< typename ConstantTypes::FOLLOWUP_TIMEOUT_MS >::Type FOLLOWUP_TIMEOUT_MS; // 500
    static const typename ::uavcan::StorageType< typename ConstantTypes::MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST >::Type MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST; // 6
    static const typename ::uavcan::StorageType< typename ConstantTypes::ANY_NODE_ID >::Type ANY_NODE_ID; // 0

    // Fields
    typename ::uavcan::StorageType< typename FieldTypes::node_id >::Type node_id;
    typename ::uavcan::StorageType< typename FieldTypes::first_part_of_unique_id >::Type first_part_of_unique_id;
    typename ::uavcan::StorageType< typename FieldTypes::unique_id >::Type unique_id;

    Allocation_()
        : node_id()
        , first_part_of_unique_id()
        , unique_id()
    {
        ::uavcan::StaticAssert<_tmpl == 0>::check();  // Usage check

#if UAVCAN_DEBUG
        /*
         * Cross-checking MaxBitLen provided by the DSDL compiler.
         * This check shall never be performed in user code because MaxBitLen value
         * actually depends on the nested types, thus it is not invariant.
         */
        ::uavcan::StaticAssert<141 == MaxBitLen>::check();
#endif
    }

    bool operator==(ParameterType rhs) const;
    bool operator!=(ParameterType rhs) const { return !operator==(rhs); }

    /**
     * This comparison is based on @ref uavcan::areClose(), which ensures proper comparison of
     * floating point fields at any depth.
     */
    bool isClose(ParameterType rhs) const;

    static int encode(ParameterType self, ::uavcan::ScalarCodec& codec,
                      ::uavcan::TailArrayOptimizationMode tao_mode = ::uavcan::TailArrayOptEnabled);

    static int decode(ReferenceType self, ::uavcan::ScalarCodec& codec,
                      ::uavcan::TailArrayOptimizationMode tao_mode = ::uavcan::TailArrayOptEnabled);

    /*
     * Static type info
     */
    enum { DataTypeKind = ::uavcan::DataTypeKindMessage };
    enum { DefaultDataTypeID = 1 };

    static const char* getDataTypeFullName()
    {
        return "uavcan.protocol.dynamic_node_id.Allocation";
    }

    static void extendDataTypeSignature(::uavcan::DataTypeSignature& signature)
    {
        signature.extend(getDataTypeSignature());
    }

    static ::uavcan::DataTypeSignature getDataTypeSignature();

};

/*
 * Out of line struct method definitions
 */

template <int _tmpl>
bool Allocation_<_tmpl>::operator==(ParameterType rhs) const
{
    return
        node_id == rhs.node_id &&
        first_part_of_unique_id == rhs.first_part_of_unique_id &&
        unique_id == rhs.unique_id;
}

template <int _tmpl>
bool Allocation_<_tmpl>::isClose(ParameterType rhs) const
{
    return
        ::uavcan::areClose(node_id, rhs.node_id) &&
        ::uavcan::areClose(first_part_of_unique_id, rhs.first_part_of_unique_id) &&
        ::uavcan::areClose(unique_id, rhs.unique_id);
}

template <int _tmpl>
int Allocation_<_tmpl>::encode(ParameterType self, ::uavcan::ScalarCodec& codec,
    ::uavcan::TailArrayOptimizationMode tao_mode)
{
    (void)self;
    (void)codec;
    (void)tao_mode;
    int res = 1;
    res = FieldTypes::node_id::encode(self.node_id, codec,  ::uavcan::TailArrayOptDisabled);
    if (res <= 0)
    {
        return res;
    }
    res = FieldTypes::first_part_of_unique_id::encode(self.first_part_of_unique_id, codec,  ::uavcan::TailArrayOptDisabled);
    if (res <= 0)
    {
        return res;
    }
    res = FieldTypes::unique_id::encode(self.unique_id, codec,  tao_mode);
    return res;
}

template <int _tmpl>
int Allocation_<_tmpl>::decode(ReferenceType self, ::uavcan::ScalarCodec& codec,
    ::uavcan::TailArrayOptimizationMode tao_mode)
{
    (void)self;
    (void)codec;
    (void)tao_mode;
    int res = 1;
    res = FieldTypes::node_id::decode(self.node_id, codec,  ::uavcan::TailArrayOptDisabled);
    if (res <= 0)
    {
        return res;
    }
    res = FieldTypes::first_part_of_unique_id::decode(self.first_part_of_unique_id, codec,  ::uavcan::TailArrayOptDisabled);
    if (res <= 0)
    {
        return res;
    }
    res = FieldTypes::unique_id::decode(self.unique_id, codec,  tao_mode);
    return res;
}

/*
 * Out of line type method definitions
 */
template <int _tmpl>
::uavcan::DataTypeSignature Allocation_<_tmpl>::getDataTypeSignature()
{
    ::uavcan::DataTypeSignature signature(0xB2A812620A11D40ULL);

    FieldTypes::node_id::extendDataTypeSignature(signature);
    FieldTypes::first_part_of_unique_id::extendDataTypeSignature(signature);
    FieldTypes::unique_id::extendDataTypeSignature(signature);

    return signature;
}

/*
 * Out of line constant definitions
 */

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::MAX_REQUEST_PERIOD_MS >::Type
    Allocation_<_tmpl>::MAX_REQUEST_PERIOD_MS = 1000U; // 1000

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::MIN_REQUEST_PERIOD_MS >::Type
    Allocation_<_tmpl>::MIN_REQUEST_PERIOD_MS = 600U; // 600

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::MAX_FOLLOWUP_DELAY_MS >::Type
    Allocation_<_tmpl>::MAX_FOLLOWUP_DELAY_MS = 400U; // 400

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::MIN_FOLLOWUP_DELAY_MS >::Type
    Allocation_<_tmpl>::MIN_FOLLOWUP_DELAY_MS = 0U; // 0

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::FOLLOWUP_TIMEOUT_MS >::Type
    Allocation_<_tmpl>::FOLLOWUP_TIMEOUT_MS = 500U; // 500

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST >::Type
    Allocation_<_tmpl>::MAX_LENGTH_OF_UNIQUE_ID_IN_REQUEST = 6U; // 6

template <int _tmpl>
const typename ::uavcan::StorageType< typename Allocation_<_tmpl>::ConstantTypes::ANY_NODE_ID >::Type
    Allocation_<_tmpl>::ANY_NODE_ID = 0U; // 0

/*
 * Final typedef
 */
typedef Allocation_<0> Allocation;

namespace
{

const ::uavcan::DefaultDataTypeRegistrator< ::uavcan::protocol::dynamic_node_id::Allocation > _uavcan_gdtr_registrator_Allocation;

}

} // Namespace dynamic_node_id
} // Namespace protocol
} // Namespace uavcan

/*
 * YAML streamer specialization
 */
namespace uavcan
{

template <>
class UAVCAN_EXPORT YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation >
{
public:
    template <typename Stream>
    static void stream(Stream& s, ::uavcan::protocol::dynamic_node_id::Allocation::ParameterType obj, const int level);
};

template <typename Stream>
void YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation >::stream(Stream& s, ::uavcan::protocol::dynamic_node_id::Allocation::ParameterType obj, const int level)
{
    (void)s;
    (void)obj;
    (void)level;
    if (level > 0)
    {
        s << '\n';
        for (int pos = 0; pos < level; pos++)
        {
            s << "  ";
        }
    }
    s << "node_id: ";
    YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation::FieldTypes::node_id >::stream(s, obj.node_id, level + 1);
    s << '\n';
    for (int pos = 0; pos < level; pos++)
    {
        s << "  ";
    }
    s << "first_part_of_unique_id: ";
    YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation::FieldTypes::first_part_of_unique_id >::stream(s, obj.first_part_of_unique_id, level + 1);
    s << '\n';
    for (int pos = 0; pos < level; pos++)
    {
        s << "  ";
    }
    s << "unique_id: ";
    YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation::FieldTypes::unique_id >::stream(s, obj.unique_id, level + 1);
}

}

namespace uavcan
{
namespace protocol
{
namespace dynamic_node_id
{

template <typename Stream>
inline Stream& operator<<(Stream& s, ::uavcan::protocol::dynamic_node_id::Allocation::ParameterType obj)
{
    ::uavcan::YamlStreamer< ::uavcan::protocol::dynamic_node_id::Allocation >::stream(s, obj, 0);
    return s;
}

} // Namespace dynamic_node_id
} // Namespace protocol
} // Namespace uavcan

#endif // UAVCAN_PROTOCOL_DYNAMIC_NODE_ID_ALLOCATION_HPP_INCLUDED