#pragma once

// Including sensors and outputs
#include "Input.h"
#include "FrdmK64f_AppShield_Input.hpp"
#include "FrdmK64f_AppShield_Output.h"
#include "FrdmK64f_Input.hpp"
#include "FrdmK64f_Output.h"

// Defining some types used to create an IO object
struct FrdmK64f
{
    typedef FrdmK64f_Input< ::Input> Input;         // If we want to use k64f only
    struct Output { FrdmK64f_Output frdmK64f; };    //

    struct AppShield
    {
        typedef FrdmK64f_AppShield_Input<FrdmK64f::Input> Input;                        // If we want to use k64f
        struct Output { FrdmK64f_Output frdmK64f; FrdmK64f_AppShield_Output appShield; };   // with application shield
    };
};

struct AppShield
{
    typedef FrdmK64f_AppShield_Input< ::Input> Input;   // If we want to use 
    struct Output { FrdmK64f_AppShield_Output appShield; }; // application shield only
};

/*
** IO Object
**
** Used to interact with the device
** input is an event manager
** output list les ouputs
*/
template <typename Platform> struct IO 
{
    static typename Platform::Input  input;
    static typename Platform::Output output;
};

template <typename Platform>
typename Platform::Input  IO<Platform>::input;

template <typename Platform>
typename Platform::Output  IO<Platform>::output;