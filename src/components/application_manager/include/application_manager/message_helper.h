/*
 Copyright (c) 2015, Ford Motor Company
 All rights reserved.

 Copyright (c) 2017, Livio, Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_MESSAGE_HELPER_H_
#define SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_MESSAGE_HELPER_H_

#include <map>
#include <vector>
#include <string>

#include "interfaces/MOBILE_API.h"
#include "interfaces/HMI_API.h"
#include "utils/macro.h"
#include "connection_handler/device.h"
#include "application_manager/application.h"
#include "policy/policy_types.h"
#include "protocol_handler/session_observer.h"
#include "application_manager/policies/policy_handler_interface.h"
#include "smart_objects/smart_object.h"
#include "transport_manager/common.h"
#include <application_manager/smart_object_keys.h>

namespace policy {
class PolicyHandlerInterface;
}

namespace application_manager {
namespace mobile_api = mobile_apis;

/*
 * @brief Typedef for VehicleData
 *
 * @param const char* Name of the parameter in mobile request
 * @param VehicleDataType Enum for vehicle data
 */
typedef std::map<std::string, mobile_apis::VehicleDataType::eType> VehicleData;

/**
 * @brief MessageHelper class
 **/
class MessageHelper {
 public:
  /**
 * @brief CreateNotification creates basic mobile notification smart object
 * @param function_id Notification function ID
 * @param app_id application to send notification
 * @return basic mobile notification smart object
 */
  static smart_objects::SmartObjectSPtr CreateNotification(
      mobile_apis::FunctionID::eType function_id, uint32_t app_id);
  /**
 * @brief CreateHMINotification creates basic hmi notification smart object
 * @param function_id Notification function ID
 * @return basic hmi notification smart object
 */
  static smart_objects::SmartObjectSPtr CreateHMINotification(
      hmi_apis::FunctionID::eType function_id);

  /**
   * @brief Creates request for different interfaces(JSON)
   * @param correlation_id unique ID
   * @param params Vector of arguments that we need in GetVehicleData request
   * (e.g. gps, odometer, fuel_level)
   */
  static void CreateGetVehicleDataRequest(
      const uint32_t correlation_id,
      const std::vector<std::string>& params,
      ApplicationManager& app_mngr);

  /**
   * @brief Create mobile HashUpdateNotification
   */
  static smart_objects::SmartObjectSPtr CreateHashUpdateNotification(
      const uint32_t app_id);

  /**
   * @brief Sends to mobile HashUpdateNotification
   */
  static void SendHashUpdateNotification(const uint32_t app_id,
                                         ApplicationManager& app_mngr);

  /**
   * @brief Sends OnLanguageChange notification to application
   * @param connection_key Connection key of application
   */
  static void SendOnLanguageChangeToMobile(uint32_t connection_key);

  /**
    * @brief Sends DecryptCertificate request to HMI
    * @param file_name path to file containing encrypted certificate
    */
  static void SendDecryptCertificateToHMI(const std::string& file_name,
                                          ApplicationManager& app_mngr);

  /**
    * @brief SendGetSystemTimeRequest sends mentioned request to HMI.
    * @param correlation_id the message correlation id, required for proper
    * response processing.
    * @param app_mngr
    */
  static void SendGetSystemTimeRequest(const uint32_t correlation_id,
                                       ApplicationManager& app_mngr);

  /*
   * @brief Retrieve vehicle data map for param name in mobile request
   * to VehicleDataType
   *
   * @return VehicleData reference
   */
  static const VehicleData& vehicle_data();

  /**
   * @brief Converts HMI Result enum value to string
   * @param hmi_result HMI Result enum value
   * @return stringified value for enum if succedeed, otherwise - empty string
   */
  static std::string HMIResultToString(
      hmi_apis::Common_Result::eType hmi_result);

  /**
   * @brief Converts string to HMI Result enum value
   * @param hmi_result stringified value
   * @return HMI Result enum value if succedeed, otherwise - INVALID_ENUM
   * value
   */
  static hmi_apis::Common_Result::eType HMIResultFromString(
      const std::string& hmi_result);

  /**
   * @brief Converts mobile Result enum value to string
   * @param mobile_result mobile Result enum value
   * @return stringified value for enum if succedeed, otherwise - empty string
   */
  static std::string MobileResultToString(
      mobile_apis::Result::eType mobile_result);

  static std::string GetDeviceMacAddressForHandle(
      const transport_manager::DeviceHandle device_handle,
      const ApplicationManager& app_mngr);
  /**
   * @brief Converts string to mobile Result enum value
   * @param mobile_result stringified value
   * @return mobile Result enum value if succedeed, otherwise - INVALID_ENUM
   * value
   */
  static mobile_api::Result::eType MobileResultFromString(
      const std::string& mobile_result);

  /**
   * @brief Converts HMI Result enum value to mobile Result enum value
   * @param hmi_result HMI Result enum value
   * @return mobile Result enum value if succedeed, otherwise - INVALID_ENUM
   * value
   */
  static mobile_api::Result::eType HMIToMobileResult(
      const hmi_apis::Common_Result::eType hmi_result);

  /**
   * @brief Converts mobile Result enum value to HMI Result enum value
   * @param mobile_result mobile Result enum value
   * @return HMI Result enum value
   */
  static hmi_apis::Common_Result::eType MobileToHMIResult(
      const mobile_api::Result::eType mobile_result);

  /**
   * @brief Convert string to HMI level, if possible
   * @param hmi_level Stringified HMI level
   * @return Appropriate enum from HMI level, or INVALID_ENUM, if conversiion
   * is not possible
   */
  static mobile_api::HMILevel::eType StringToHMILevel(
      const std::string& hmi_level);

  /*
  * @brief Used to obtain string representation of app's
  * HMI Level.
  * @param hmi_level Desired HMI Level
  */
  static std::string StringifiedHMILevel(
      const mobile_apis::HMILevel::eType hmi_level);

  /*
  * @brief Used to obtain function name by its id
  * @param function_id Function ID
  */
  static std::string StringifiedFunctionID(
      mobile_apis::FunctionID::eType function_id);

  static smart_objects::SmartObjectSPtr CreateBlockedByPoliciesResponse(
      mobile_apis::FunctionID::eType function_id,
      mobile_apis::Result::eType result,
      const uint32_t correlation_id,
      uint32_t connection_key);

  /*
   * @brief Prepare GetDeviceListResponse
   *
   *
   * @param devices Devices list
   *
   */
  static smart_objects::SmartObjectSPtr CreateDeviceListSO(
      const connection_handler::DeviceMap& devices,
      const policy::PolicyHandlerInterface& policy_handler,
      ApplicationManager& app_mngr);

  static smart_objects::SmartObjectSPtr CreateModuleInfoSO(
      uint32_t function_id, ApplicationManager& app_mngr);

  static smart_objects::SmartObjectSPtr CreateSetAppIcon(
      const std::string& path_to_icon, uint32_t app_id);

  /**
   * @brief Sends button subscription notification
   */
  static void SendOnButtonSubscriptionNotification(
      const uint32_t app_id,
      const hmi_apis::Common_ButtonName::eType button,
      const bool is_subscribed,
      ApplicationManager& app_mngr);

  /**
   * @brief Sends button subscription notifications for all buttons
   * that application is subscribed on
   */
  static void SendAllOnButtonSubscriptionNotificationsForApp(
      ApplicationConstSharedPtr app, ApplicationManager& app_mngr);

  static void SendAppDataToHMI(ApplicationConstSharedPtr app,
                               ApplicationManager& app_man);
  static void SendGlobalPropertiesToHMI(ApplicationConstSharedPtr app,
                                        ApplicationManager& app_mngr);
  static smart_objects::SmartObjectList CreateGlobalPropertiesRequestsToHMI(
      ApplicationConstSharedPtr app, const uint32_t correlation_id);

  static smart_objects::SmartObjectSPtr CreateAppVrHelp(
      ApplicationConstSharedPtr app);

  static smart_objects::SmartObjectList CreateShowRequestToHMI(
      ApplicationConstSharedPtr app, const uint32_t correlation_id);
  static void SendShowRequestToHMI(ApplicationConstSharedPtr app,
                                   ApplicationManager& app_mngr);
  static void SendShowConstantTBTRequestToHMI(ApplicationConstSharedPtr app,
                                              ApplicationManager& app_man);
  static void SendAddCommandRequestToHMI(ApplicationConstSharedPtr app,
                                         ApplicationManager& app_man);
  static smart_objects::SmartObjectList CreateAddCommandRequestToHMI(
      ApplicationConstSharedPtr app, ApplicationManager& app_mngr);

  static smart_objects::SmartObjectList
  CreateAddVRCommandRequestFromChoiceToHMI(ApplicationConstSharedPtr app,
                                           ApplicationManager& app_mngr);

  /**
   * @brief Sends UI_ChangeRegistration to HMI with list of AppHMIType
   * @param app applicaton instace
   */
  static void SendUIChangeRegistrationRequestToHMI(
      ApplicationConstSharedPtr app, ApplicationManager& app_mngr);
  static void SendAddVRCommandToHMI(
      uint32_t cmd_id,
      const smart_objects::SmartObject& vr_commands,
      const uint32_t app_id,
      ApplicationManager& app_mngr);

  static smart_objects::SmartObjectSPtr CreateAddVRCommandToHMI(
      uint32_t cmd_id,
      const smart_objects::SmartObject& vr_commands,
      const uint32_t app_id,
      ApplicationManager& app_mngr);

  /*
   * @brief Create Common.DeviceInfo struct from device handle
   * @param device_handle device handle of the app
   * @param session_observer instance of SessionObserver to retrieve device
   * information
   * @param policy_handler instance of PolicyHandlerInterface to get the value
   * of 'isSDLAllowed'
   * @param app_mngr instance of ApplicationManager
   * @param output smart object to store created Common.DeviceInfo struct
   * @return true on success, false otherwise
   */
  static bool CreateDeviceInfo(
      connection_handler::DeviceHandle device_handle,
      const protocol_handler::SessionObserver& session_observer,
      const policy::PolicyHandlerInterface& policy_handler,
      ApplicationManager& app_mngr,
      smart_objects::SmartObject* output);

  /*
   * @brief Create Common.HMIApplication struct application instance
   * @param app : applicaton instace
   * @param output smart object to store Common.HMIApplication struct
   * @return true on succes, otherwise return false;
   */
  static bool CreateHMIApplicationStruct(
      ApplicationConstSharedPtr app,
      const protocol_handler::SessionObserver& session_observer,
      const policy::PolicyHandlerInterface& policy_handler,
      smart_objects::SmartObject* output,
      ApplicationManager& app_mngr);

  static void SendAddSubMenuRequestToHMI(ApplicationConstSharedPtr app,
                                         ApplicationManager& app_mngr);
  static smart_objects::SmartObjectList CreateAddSubMenuRequestToHMI(
      ApplicationConstSharedPtr app, const uint32_t correlation_id);

  /*
   * @brief Creates BasicCommunication.OnAppUnregistered notification
   * @param app Application instance
   * @param is_unexpected_disconnect
   * Indicates if connection was unexpectedly lost by TM or HB
   */
  static void SendOnAppUnregNotificationToHMI(ApplicationConstSharedPtr app,
                                              bool is_unexpected_disconnect,
                                              ApplicationManager& app_mngr);

  static ns_smart_device_link::ns_smart_objects::SmartObjectSPtr
  GetBCActivateAppRequestToHMI(
      ApplicationConstSharedPtr app,
      const protocol_handler::SessionObserver& session_observer,
      const policy::PolicyHandlerInterface& policy_handler,
      hmi_apis::Common_HMILevel::eType level,
      bool send_policy_priority,
      ApplicationManager& app_mngr);

  static void SendOnResumeAudioSourceToHMI(const uint32_t app_id,
                                           ApplicationManager& app_mngr);

  /**
  * @brief Send SDL_ActivateApp response to HMI
  * @param permissions response parameters
  */
  static void SendSDLActivateAppResponse(policy::AppPermissions& permissions,
                                         uint32_t correlation_id,
                                         ApplicationManager& app_mngr);

  /**
  * @brief Send OnSDLConsentNeeded to HMI for device data consent by user
  * @param device_info Device info, e.g. mac, handle, name
  */
  static void SendOnSDLConsentNeeded(const policy::DeviceParams& device_info,
                                     ApplicationManager& app_man);

  /**
    * @brief Send request to SyncP process to read file and send
    * Policy Table Snapshot using Retry Strategy
    * @param file_path Path to file with PTS
    * @param timeout Timeout to wait for PTU in seconds
    * @param retries Seconds between retries
    */
  static void SendPolicyUpdate(const std::string& file_path,
                               const uint32_t timeout,
                               const std::vector<int>& retries,
                               ApplicationManager& app_mngr);

  /**
   * @brief Send GetUserFriendlyMessage response to HMI
   * @param msg Appopriate messages params
   * @param correlation_id Correlation id of request
   */
  static void SendGetUserFriendlyMessageResponse(
      const std::vector<policy::UserFriendlyMessage>& msg,
      uint32_t correlation_id,
      ApplicationManager& app_mngr);

/**
 * @brief Send GetListOfPermissions response to HMI
 * @param permissions Array of groups permissions
 * @param external_consent_status External user consent status
 * @param correlation_id Correlation id of request
 */
#ifdef EXTERNAL_PROPRIETARY_MODE
  static void SendGetListOfPermissionsResponse(
      const std::vector<policy::FunctionalGroupPermission>& permissions,
      const policy::ExternalConsentStatus& external_consent_status,
      const uint32_t correlation_id,
      ApplicationManager& app_mngr);
#else
  static void SendGetListOfPermissionsResponse(
      const std::vector<policy::FunctionalGroupPermission>& permissions,
      const uint32_t correlation_id,
      ApplicationManager& app_mngr);
#endif  // EXTERNAL_PROPRIETARY_MODE

  /*
   * @brief Sends SetVideoConfig request to HMI to negotiate video parameters
   *
   * @param app_id       the application which will start video streaming
   * @param app_mngr     reference of application manager
   * @param video_params parameters of video streaming, notified by mobile
   */
  static void SendNaviSetVideoConfig(
      int32_t app_id,
      ApplicationManager& app_mngr,
      const smart_objects::SmartObject& video_params);

  /*
   * @brief Sends notification to HMI to start video streaming
   *
   * @param connection_key  Application connection key
   *
   */
  static void SendNaviStartStream(int32_t app_id, ApplicationManager& app_mngr);

  /*
   * @brief Sends notification to HMI to stop video streaming
   *
   * @param connection_key  Application connection key
   *
   */
  static void SendNaviStopStream(int32_t app_id, ApplicationManager& app_mngr);

  /*
  * @brief Send notification for Update of Policy Table
  * with PT Snapshot.
  * @param connection_key Id of application to send message to
  * @param policy_data PT Snapshot
  * @param url If empty string, no URL is provided
  * @param timeout If -1 no timeout is provdied
  */
  static void SendPolicySnapshotNotification(
      uint32_t connection_key,
      const std::vector<uint8_t>& policy_data,
      const std::string& url,
      ApplicationManager& app_mngr);

  static void SendSystemRequestNotification(
      uint32_t connection_key,
      ns_smart_device_link::ns_smart_objects::SmartObject& content,
      ApplicationManager& app_mngr);

  /**
   * @brief SendLaunchApp allows to send OnSystemRequest with LAUNCH_UP.
   *
   * @param connection_key application id.
   *
   * @param urlSchema application's url schema.
   *
   * @param packageName application's package name.
   */
  static void SendLaunchApp(const uint32_t connection_key,
                            const std::string& urlSchema,
                            const std::string& packageName,
                            ApplicationManager& app_man);

  /**
   * @brief Sends OnSystemRequest which queries remote apps list
   * @param connection_key application id, which is used for sending out
   */
  static void SendQueryApps(const uint32_t connection_key,
                            ApplicationManager& app_man);

  /*
  * @brief Send notification to mobile on application permissions update
  * @param connection_key Id of application to send message to
  * @param permissions updated permissions for application
  */
  static void SendOnPermissionsChangeNotification(
      uint32_t connection_key,
      const policy::Permissions& permissions,
      ApplicationManager& app_mngr);

  /*
  * @brief Send notification to HMI on application permissions update
  * @param connection_key Id of application to send message to
  * @param permissions updated permissions for application
  */
  static void SendOnAppPermissionsChangedNotification(
      uint32_t connection_key,
      const policy::AppPermissions& permissions,
      ApplicationManager& app_mngr);

  /**
   * @brief Send GetStatusUpdate response to HMI with current policy update
   * status
   * @param status Update status
   * @param correlation_id Correlation id from request
   */
  static void SendGetStatusUpdateResponse(const std::string& status,
                                          const uint32_t correlation_id,
                                          ApplicationManager& app_mngr);

  /**
   * @brief Send UpdateSDL response to HMI with policy update result
   * @param result Update result
   * @param correlation_id Correlation id from request
   */
  static void SendUpdateSDLResponse(const std::string& result,
                                    const uint32_t correlation_id,
                                    ApplicationManager& app_mngr);

  /**
   * @brief Send OnStatusUpdate to HMI on policy update status change
   * @param status Policy table update status
   */
  static void SendOnStatusUpdate(const std::string& status,
                                 ApplicationManager& app_mngr);

  /**
   * @brief Send GetSystemInfo request to HMI
   */
  static void SendGetSystemInfoRequest(ApplicationManager& app_mngr);

  /*
   * @brief Sends notification to HMI to start audio streaming
   *
   * @param connection_key  Application connection key
   *
   */
  static void SendAudioStartStream(int32_t app_id,
                                   ApplicationManager& app_mngr);

  /*
   * @brief Sends notification to HMI to stop audio streaming
   *
   * @param connection_key  Application connection key
   *
   */
  static void SendAudioStopStream(int32_t connection_key,
                                  ApplicationManager& app_mngr);

  static void SendOnDataStreaming(protocol_handler::ServiceType service,
                                  bool available,
                                  ApplicationManager& app_mngr);

  /*
   * @brief Sends notification to HMI to stop audioPathThru
   *
   * @param connection_key  Application connection key
   *
   * @return TRUE on SUCCES otherwise return FALSE
   */
  static bool SendStopAudioPathThru(ApplicationManager& app_mngr);

  /**
   * @brief Sends UnsubscribeWayPoints request
   * @return true if UnsubscribedWayPoints is send otherwise false
   */
  static bool SendUnsubscribedWayPoints(ApplicationManager& app_mngr);

  static smart_objects::SmartObjectSPtr CreateNegativeResponse(
      uint32_t connection_key,
      int32_t function_id,
      const uint32_t correlation_id,
      int32_t result_code);

  /**
   * @brief Get the full file path of an app file
   *
   * @param file_name The relative path of an application file
   * @param app Current application
   * @param app_mngr Application manager
   *
   * @return The full file path of the application file if valid,
   * empty string otherwise
   */
  static std::string GetAppFilePath(std::string file_name,
                                    ApplicationConstSharedPtr app,
                                    ApplicationManager& app_mngr);

  /**
   * @brief Verify that all ttsChunks with FILE type
   * in an array include an existing file and set full path
   *
   * @param tts_chunks SmartObject with an array of TTSChunks
   * @param app Current application
   * @param app_mngr Application manager
   *
   * @return FILE_NOT_FOUND if one of the TTSChunks
   * included a file which wasn't present on disk,
   * SUCCESS otherwise
   */
  static mobile_apis::Result::eType VerifyTtsFiles(
      smart_objects::SmartObject& tts_chunks,
      ApplicationConstSharedPtr app,
      ApplicationManager& app_mngr);

  /**
    * @brief Verify image and add image file full path
    * and add path, although the image doesn't exist
    * @param SmartObject with image
    * @param app current application
    * @return verification result
    */
  static void ApplyImagePath(smart_objects::SmartObject& image,
                             ApplicationConstSharedPtr app,
                             ApplicationManager& app_mngr);

  /*
   * @brief Verify image and add image file full path
   *
   * @param SmartObject with image
   *
   * @param app current application
   *
   * @return verification result
   *
   */
  static mobile_apis::Result::eType VerifyImage(
      smart_objects::SmartObject& image,
      ApplicationConstSharedPtr app,
      ApplicationManager& app_mngr);

  /**
  * @brief Stores whether each choice in a set has the vrCommands parameter
  * MIXED means some choices have vrCommands and others don't
  * ALL means all do, NONE means none do
  */
  enum ChoiceSetVRCommandsStatus { MIXED, ALL, NONE };

  /**
   * @brief Check whether each choice in the set has the vrCommands parameter
   * @param choice set to check
   * @return a ChoiceSetVRCommandsStatus with the state of the choice set
   */
  static ChoiceSetVRCommandsStatus CheckChoiceSetVRCommands(
      const smart_objects::SmartObject& choice_set);

  /*
   * @brief Finds "Image" structure in request and verify image file presence
   *                      in Core.
   *
   * @param message SmartObject with request
   *
   * @param app current application
   *
   * @return verification result
   *
   */
  static mobile_apis::Result::eType VerifyImageFiles(
      smart_objects::SmartObject& message,
      ApplicationConstSharedPtr app,
      ApplicationManager& app_mngr);

  static mobile_apis::Result::eType VerifyImageVrHelpItems(
      smart_objects::SmartObject& message,
      ApplicationConstSharedPtr app,
      ApplicationManager& app_mngr);

  /**
   * @brief Checks string if it contains incorrect character \t\n \\t \\n
   * or string contains only whitespace
   * @param parameter str contains string which must be checked
   * @return returns FALSE if string contains incorrect character or
   * string is empty otherwise returns TRUE
   */
  static bool VerifyString(const std::string& str);

  static mobile_apis::Result::eType ProcessSoftButtons(
      smart_objects::SmartObject& message_params,
      ApplicationConstSharedPtr app,
      const policy::PolicyHandlerInterface& policy_handler,
      ApplicationManager& app_mngr);

  /*
   * @brief subscribe application to softbutton
   *
   * @param message_params contains data of request
   *
   * @param app current application
   *
   * @param function_id Unique command id from mobile API
   */
  static void SubscribeApplicationToSoftButton(
      smart_objects::SmartObject& message_params,
      ApplicationSharedPtr app,
      int32_t function_id);

  /**
   * @brief Prints SmartObject contents to log file
   * @param object - SmartObject to print
   * @return always True as this function is used for internal debug purposes
   * only
   * @note Function prints SmartObject only in DEBUG build mode. There will not
   * be any print in RELEASE build mode
   */
  static bool PrintSmartObject(const smart_objects::SmartObject& object);

  template <typename From, typename To>
  static To ConvertEnumAPINoCheck(const From& input) {
    return static_cast<To>(input);
  }

  static const uint32_t GetPriorityCode(const std::string& priority);
  /**
   * @brief Convert common language to string representation
   * @param language Common language
   * @return Common language string representation
   */
  static std::string CommonLanguageToString(
      hmi_apis::Common_Language::eType language);

  /**
   * @brief Converts string to mobile language enum value
   * @param language language as string
   * @return Mobile language enum value
   */
  static mobile_apis::Language::eType MobileLanguageFromString(
      const std::string& language);

  /**
   * @brief Converts mobile language enum to HMI language enum
   * @param language Mobile language enum
   * @return HMI language enum
   */
  static hmi_apis::Common_Language::eType MobileToCommonLanguage(
      const mobile_apis::Language::eType language);

  /**
   * @brief Converts HMI language enum to mobile language enum
   * @param language HMI language enum
   * @return Mobile language enum
   */
  static mobile_apis::Language::eType CommonToMobileLanguage(
      const hmi_apis::Common_Language::eType language);

  /**
   * @brief Gets command limit number per minute for specific application
   * @param policy_app_id Unique application id
   * @return Limit for number of command per minute
   */
  static uint32_t GetAppCommandLimit(const std::string& policy_app_id);

  /**
   * @brief Creates TTS.SetGlobalProperties request and sends
   * to HMI for VCA module.
   * @param app contains application which sends TTS GlobalProperties to HMI
   * after timeout or first time when application register with level NONE or
   * BACKGROUND
   * @param default_help_prompt
   * if default_help_prompt=TRUE->TTSGlobalProperties request will be created
   * with
   * default helpPrompt array, otherwise TTSGlobalProperties request will be
   * created
   * with empty helpPrompt array.
   */
  static void SendTTSGlobalProperties(ApplicationSharedPtr app,
                                      const bool default_help_prompt,
                                      ApplicationManager& app_man);

  /**
   * @brief SendSetAppIcon allows to send SetAppIcon request.
   *
   * @param app_id application for which icon request should be sent.
   *
   * @param icon_path path to the icon.
   */
  static void SendSetAppIcon(const uint32_t app_id,
                             const std::string& icon_path,
                             ApplicationManager& application_manager);

  static hmi_apis::Common_Language::eType CommonLanguageFromString(
      const std::string& language);

  /**
   * @brief CommonLightNameFromString convert string to LightName enum value
   * @param lightName string to convert
   * @return value LightName enum value
   */
  static hmi_apis::Common_LightName::eType CommonLightNameFromString(
      const std::string& lightName);

  static smart_objects::SmartObjectSPtr
  GetOnAppInterfaceUnregisteredNotificationToMobile(
      int32_t connection_key,
      mobile_api::AppInterfaceUnregisteredReason::eType reason);

  /**
   * @brief SendDeleteCommandRequest sends requests to HMI to remove UI/VR
   * command data depending on command parameters
   * @param cmd Command data
   * @param application Application owning the command data
   * @param app_mngr Application manager
   */
  static void SendDeleteCommandRequest(smart_objects::SmartObject* cmd,
                                       ApplicationSharedPtr application,
                                       ApplicationManager& app_mngr);

  /**
   * @brief SendDeleteSubmenuRequest sends UI/VR requests to HMI to remove
   * submenues-related data depending on command parameters
   * @param cmd Command data
   * @param application Application owning the commmand data
   * @param app_mngr Application manager
   */
  static void SendDeleteSubmenuRequest(smart_objects::SmartObject* cmd,
                                       ApplicationSharedPtr application,
                                       ApplicationManager& app_mngr);

  /**
   * @brief SendDeleteChoiceSetRequest sends requests to HMI to remove
   * choice sets - related data depending on command parameters
   * @param cmd Command data
   * @param application Application owning command data
   * @param app_mngr Application manager
   */
  static void SendDeleteChoiceSetRequest(smart_objects::SmartObject* cmd,
                                         ApplicationSharedPtr application,
                                         ApplicationManager& app_mngr);

  /**
   * @brief SendResetPropertiesRequest sends requests to HMI to remove/reset
   * global properties for application
   * @param application Application to remove/reset global properties for
   * @param app_mngr Application manager
   */
  static void SendResetPropertiesRequest(ApplicationSharedPtr application,
                                         ApplicationManager& app_mngr);

  /**
   * @brief SendUnsubscribeButtonNotification sends notification to HMI to
   * remove button subscription for application
   * @param button Button type
   * @param application Application to unsubscribe
   * @param app_mngr Application manager
   */
  static void SendUnsubscribeButtonNotification(
      mobile_apis::ButtonName::eType button,
      ApplicationSharedPtr application,
      ApplicationManager& app_mngr);

  /**
   * @brief Sends HMI status notification to mobile
   * @param application_impl application with changed HMI status
   **/
  static void SendHMIStatusNotification(
      const Application& application_impl,
      ApplicationManager& application_manager);

  /**
   * @brief SendActivateAppToHMI Sends BasicCommunication.ActivateApp request to
   * HMI
   * @param app_id Application id
   * @param application_manager Application manager
   * @param level Application HMI level
   * @param send_policy_priority Defines whether to send "priority" field with
   * request
   */
  static void SendActivateAppToHMI(
      uint32_t const app_id,
      ApplicationManager& application_manager,
      hmi_apis::Common_HMILevel::eType level = hmi_apis::Common_HMILevel::FULL,
      bool send_policy_priority = true);

  /**
   * @brief CreateMessageForHMI Creates HMI message with prepared header
   * acccoring to message type
   * @param message_type Message type
   * @param correlation_id Correlation id
   * @return HMI message object with filled header
   */
  static smart_objects::SmartObjectSPtr CreateMessageForHMI(
      hmi_apis::messageType::eType message_type, const uint32_t correlation_id);

  static smart_objects::SmartObject CreateAppServiceCapabilities(
      std::vector<smart_objects::SmartObject>& all_services);

  static void BroadcastCapabilityUpdate(smart_objects::SmartObject& msg_params,
                                        ApplicationManager& app_mngr);

 private:
  /**
   * @brief Allows to fill SO according to the  current permissions.
   * @param permissions application permissions.
   * @param message which should be filled.
   */
  static void FillAppRevokedPermissions(
      const policy::AppPermissions& permissions,
      smart_objects::SmartObject& message);

  static smart_objects::SmartObjectSPtr CreateChangeRegistration(
      const int32_t function_id,
      const int32_t language,
      const uint32_t app_id,
      const smart_objects::SmartObject* app_types,
      ApplicationManager& app_mngr);

  MessageHelper();

  static const VehicleData vehicle_data_;
  DISALLOW_COPY_AND_ASSIGN(MessageHelper);
};

}  // namespace application_manager

#endif  // SRC_COMPONENTS_APPLICATION_MANAGER_INCLUDE_APPLICATION_MANAGER_MESSAGE_HELPER_H_
