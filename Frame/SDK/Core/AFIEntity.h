/*
* This source file is part of ArkGameFrame
* For the latest info, see https://github.com/ArkGame
*
* Copyright (c) 2013-2017 ArkGame authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#pragma once

#include "SDK/Base/AFPlatform.hpp"
#include "SDK/Base/AFCDataList.h"
#include "AFRecord.h"
#include "AFIRecordMgr.h"
#include "AFIHeartBeatManager.h"
#include "AFIPropertyMgr.h"
#include "AFIEventManager.h"
#include "SDK/Interface/AFIPluginManager.h"

class AFIEntity
{
public:
    AFIEntity(const AFGUID& self) {}

    virtual ~AFIEntity() {}

    virtual bool Execute() = 0;
    virtual const AFGUID& Self() = 0;

    template<typename BaseType>
    bool AddPropertyCallBack(const std::string& strPropertyName, BaseType* pBase, int (BaseType::*handler)(const AFGUID&, const std::string&, const AFIData&, const AFIData&))
    {
        PROPERTY_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        PROPERTY_EVENT_FUNCTOR_PTR functorPtr(ARK_NEW PROPERTY_EVENT_FUNCTOR(functor));
        return AddPropertyCallBack(strPropertyName, functorPtr);
    }

    template<typename BaseType>
    bool AddRecordCallBack(const std::string& strRecordName, BaseType* pBase, int (BaseType::*handler)(const AFGUID&, const RECORD_EVENT_DATA&, const AFIData&, const AFIData&))
    {
        RECORD_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        RECORD_EVENT_FUNCTOR_PTR functorPtr(ARK_NEW RECORD_EVENT_FUNCTOR(functor));
        return AddRecordCallBack(strRecordName, functorPtr);
    }

    template<typename BaseType>
    bool AddHeartBeat(const std::string& strHeartBeatName, BaseType* pBase, int (BaseType::*handler)(const AFGUID&, const std::string&, const float, const int), const float fTime, const int nCount, const bool bForever)
    {
        HEART_BEAT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        HEART_BEAT_FUNCTOR_PTR functorPtr(ARK_NEW HEART_BEAT_FUNCTOR(functor));
        return AddHeartBeat(strHeartBeatName, functorPtr, fTime, nCount,  bForever);
    }

    virtual bool FindHeartBeat(const std::string& strHeartBeatName) = 0;
    virtual bool RemoveHeartBeat(const std::string& strHeartBeatName) = 0;

    virtual bool FindProperty(const std::string& strPropertyName) = 0;

    virtual bool SetPropertyBool(const std::string& strPropertyName, const bool value) = 0;
    virtual bool SetPropertyInt(const std::string& strPropertyName, const int32_t value) = 0;
    virtual bool SetPropertyInt64(const std::string& strPropertyName, const int64_t value) = 0;
    virtual bool SetPropertyFloat(const std::string& strPropertyName, const float value) = 0;
    virtual bool SetPropertyDouble(const std::string& strPropertyName, const double value) = 0;
    virtual bool SetPropertyString(const std::string& strPropertyName, const std::string& value) = 0;
    virtual bool SetPropertyObject(const std::string& strPropertyName, const AFGUID& value) = 0;

    virtual bool GetPropertyBool(const std::string& strPropertyName) = 0;
    virtual int32_t GetPropertyInt(const std::string& strPropertyName) = 0;
    virtual int64_t GetPropertyInt64(const std::string& strPropertyName) = 0;
    virtual float GetPropertyFloat(const std::string& strPropertyName) = 0;
    virtual double GetPropertyDouble(const std::string& strPropertyName) = 0;
    virtual const char*  GetPropertyString(const std::string& strPropertyName) = 0;
    virtual const AFGUID& GetPropertyObject(const std::string& strPropertyName) = 0;

    virtual bool FindRecord(const std::string& strRecordName) = 0;

    virtual bool SetRecordBool(const std::string& strRecordName, const int nRow, const int nCol, const bool value) = 0;
    virtual bool SetRecordInt(const std::string& strRecordName, const int nRow, const int nCol, const int32_t value) = 0;
    virtual bool SetRecordInt64(const std::string& strRecordName, const int nRow, const int nCol, const int64_t value) = 0;
    virtual bool SetRecordFloat(const std::string& strRecordName, const int nRow, const int nCol, const float value) = 0;
    virtual bool SetRecordDouble(const std::string& strRecordName, const int nRow, const int nCol, const double value) = 0;
    virtual bool SetRecordString(const std::string& strRecordName, const int nRow, const int nCol, const std::string& value) = 0;
    virtual bool SetRecordObject(const std::string& strRecordName, const int nRow, const int nCol, const AFGUID& value) = 0;

    virtual bool GetRecordBool(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual int32_t GetRecordInt(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual int64_t GetRecordInt64(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual float GetRecordFloat(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual double GetRecordDouble(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const char* GetRecordString(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const AFGUID& GetRecordObject(const std::string& strRecordName, const int nRow, const int nCol) = 0;

    virtual ARK_SHARE_PTR<AFIRecordMgr> GetRecordManager() = 0;
    virtual ARK_SHARE_PTR<AFIHeartBeatManager> GetHeartBeatManager() = 0;
    virtual ARK_SHARE_PTR<AFIPropertyMgr> GetPropertyManager() = 0;
    virtual ARK_SHARE_PTR<AFIEventManager> GetEventManager() = 0;

protected:

    virtual bool AddRecordCallBack(const std::string& strRecordName, const RECORD_EVENT_FUNCTOR_PTR& cb) = 0;
    virtual bool AddPropertyCallBack(const std::string& strPropertyName, const PROPERTY_EVENT_FUNCTOR_PTR& cb) = 0;
    virtual bool AddHeartBeat(const std::string& strHeartBeatName, const HEART_BEAT_FUNCTOR_PTR& cb, const int64_t nTime, const int nCount, const bool bForever) = 0;

protected:
    AFIPluginManager* m_pPluginManager;
};