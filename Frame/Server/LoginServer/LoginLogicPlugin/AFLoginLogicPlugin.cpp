// -------------------------------------------------------------------------
//    @FileName         :    NFLoginLogicPlugin.cpp
//    @Author           :    Ark Game Tech
//    @Date             :    2012-07-14 08:51
//    @Module           :    LoginLogicPluginModule
//
// -------------------------------------------------------------------------


#include "AFLoginLogicPlugin.h"
#include "AFCLoginLogicModule.h"

//
#ifdef NF_DYNAMIC_PLUGIN

ARK_EXPORT void DllStartPlugin(AFIPluginManager* pm)
{
#if ARK_PLATFORM == PLATFORM_WIN
    SetConsoleTitle("NFLoginServer");
#endif
    CREATE_PLUGIN(pm, NFLoginLogicPlugin)

};

ARK_EXPORT void DllStopPlugin(AFIPluginManager* pm)
{
    DESTROY_PLUGIN(pm, NFLoginLogicPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int NFLoginLogicPlugin::GetPluginVersion()
{
    return 0;
}

const std::string NFLoginLogicPlugin::GetPluginName()
{
    return GET_CLASS_NAME(NFLoginLogicPlugin);
}

void NFLoginLogicPlugin::Install()
{

    REGISTER_MODULE(pPluginManager, AFILoginLogicModule, AFCLoginLogicModule)

}

void NFLoginLogicPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, AFILoginLogicModule, AFCLoginLogicModule)
}
