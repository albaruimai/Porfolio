//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include <vector>
#include <memory>
#include <concepts>
#include "node.hpp"

template <typename T>
concept BTNodeType = std::derived_from<T, BTNode_t>;

struct BehaviourTree_t{
    using value_type = std::unique_ptr<BTNode_t, BTNode_t::Deleter>;
    using NodeStorage_t = std::vector<value_type>;
    using MemoryStorage_t = std::unique_ptr<std::byte[]>;


BTNodeStatus_t run(EntityContext_t &&ectx) noexcept {return run(ectx);}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept {
        if(nodes.size() > 0){
            return nodes.back()->run(ectx);
        }
        return BTNodeStatus_t::fail;
    };

    template <BTNodeType NodeType, typename... ParamTypes>
    NodeType& createNode(ParamTypes&&... params){
        ptr_reserved -= sizeof(NodeType);
        if(ptr_reserved < mem.get()){
            ptr_reserved += sizeof(NodeType);
            throw std::bad_alloc{};
        }
        auto* pnode { new (ptr_reserved) NodeType{ std::forward<ParamTypes>(params)...} };
        nodes.emplace_back(pnode);

        return *pnode;
    }

    private:
        std::size_t     mem_size     { 4096 };
        MemoryStorage_t mem          { std::make_unique<std::byte[]>(mem_size) };
        std::byte*      ptr_reserved { mem.get() + mem_size };
        NodeStorage_t   nodes        {};
};