//
//  DNASequencer.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/29/15.
//
//
#include <fstream>

#include "rapidjson/document.h"

#include "DNASequencer.h"
#include "EntitySystem.h"

Entity* DNASequencer::CreateEntity( std::string i_dnaPath )
{
    Entity* pEntity = EntitySystem::CreateEntity();
    
    std::ifstream f( i_dnaPath );
    std::string content( (std::istreambuf_iterator<char>(f) ),
                        (std::istreambuf_iterator<char>()    ) );
    rapidjson::Document pDocument;
    pDocument.Parse( content.c_str() );
    
    
    pEntity->SetName( pDocument["Name"].GetString() );
    printf( "Creating Entity '%s'\n", pEntity->GetName().c_str() );
    
    for (rapidjson::Value::ConstMemberIterator itr = pDocument["Components"].MemberBegin();
         itr != pDocument["Components"].MemberEnd(); ++itr)
    {
        printf( "  Attaching component %s\n", itr->name.GetString() );
        
        if ( itr->value.GetType() == rapidjson::Type::kObjectType )
        {
            EntitySystem::AttachComponent( pEntity->m_entityHandle, itr->name.GetString(), itr->value );
        }
    }
    
    
    return pEntity;
}

uint32_t DNASequencer::CreateCollisionCategory( const rapidjson::Value& i_dnaObject )
{
    uint32_t pCategory = 0;
    bool first = true;
    for ( rapidjson::Value::ConstValueIterator itr = i_dnaObject.Begin(); itr != i_dnaObject.End(); ++itr )
    {
        if ( first )
        {
            pCategory = PhysicsSystem::GetCollisionCategory( itr->GetString() );
            first = false;
        }
        else
        {
            pCategory |= PhysicsSystem::GetCollisionCategory( itr->GetString() );
        }
    }
    return pCategory;
}