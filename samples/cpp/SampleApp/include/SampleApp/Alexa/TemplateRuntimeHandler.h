/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef SAMPLEAPP_ALEXA_TEMPLATERUNTIMEHANDLER_H
#define SAMPLEAPP_ALEXA_TEMPLATERUNTIMEHANDLER_H

#include "SampleApp/Activity.h"
#include "SampleApp/Logger/LoggerHandler.h"

#include <AACE/Alexa/TemplateRuntime.h>

namespace sampleApp {
namespace alexa {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  TemplateRuntimeHandler
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class TemplateRuntimeHandler : public aace::alexa::TemplateRuntime /* isa PlatformInterface */ {
  private:
    std::weak_ptr<Activity> m_activity{};
    std::weak_ptr<logger::LoggerHandler> m_loggerHandler{};

  protected:
    TemplateRuntimeHandler(std::weak_ptr<Activity> activity, std::weak_ptr<logger::LoggerHandler> loggerHandler);

  public:
    template <typename... Args> static auto create(Args &&... args) -> std::shared_ptr<TemplateRuntimeHandler> {
        return std::shared_ptr<TemplateRuntimeHandler>(new TemplateRuntimeHandler(args...));
    }
    auto getActivity() -> std::weak_ptr<Activity>;
    auto getLoggerHandler() -> std::weak_ptr<logger::LoggerHandler>;

    // aace::alexa::TemplateRuntime interface

    auto renderTemplate(const std::string &payload) -> void override;
    auto clearTemplate() -> void override;
    auto renderPlayerInfo(const std::string &payload) -> void override;
    auto clearPlayerInfo() -> void override;

  private:
    std::weak_ptr<View> m_console{};
    std::chrono::time_point<std::chrono::system_clock> m_startPlayerInfo{};
    std::chrono::time_point<std::chrono::system_clock> m_startTemplate{};
    
    std::chrono::time_point<std::chrono::steady_clock> m_whenCachedLastpayload{};
    std::string m_lastPayload;

    auto log(logger::LoggerHandler::Level level, const std::string &message) -> void;
    auto setupUI() -> void;
    auto wasPayloadJustSeen(const std::string &payload) -> bool;
};

} // namespace alexa
} // namespace sampleApp

#endif // SAMPLEAPP_ALEXA_TEMPLATERUNTIMEHANDLER_H
