
# IoTHubMQTTTransport Requirements
================

## Overview

IoTHubMQTTTransport is the library that enables communications with the iothub system using the MQTT protocol.


## Exposed API

```c
extern const TRANSPORT_PROVIDER* MQTT_Protocol(void);
```
  The following static functions are provided in the fields of the TRANSPORT_PROVIDER structure:

    - IoTHubTransportMqtt_Subscribe_DeviceMethod,
    - IoTHubTransportMqtt_Unsubscribe_DeviceMethod,
    - IoTHubTransportMqtt_Subscribe_DeviceTwin,
    - IoTHubTransportMqtt_Unsubscribe_DeviceTwin,
    - IoTHubTransportMqtt_ProcessItem,
    - IoTHubTransportMqtt_GetHostname,
    - IoTHubTransportMqtt_SetOption,
    - IoTHubTransportMqtt_Create,
    - IoTHubTransportMqtt_Destroy,
    - IoTHubTransportMqtt_Register,
    - IoTHubTransportMqtt_Unregister,
    - IoTHubTransportMqtt_Subscribe,
    - IoTHubTransportMqtt_Unsubscribe,
    - IoTHubTransportMqtt_DoWork,
    - IoTHubTransportMqtt_GetSendStatus


## IoTHubTransportMqtt_Create
```c
TRANSPORT_LL_HANDLE IoTHubTransportMqtt_Create(const IOTHUBTRANSPORT_CONFIG* config)
```
IoTHubTransportMqtt_Create shall create a TRANSPORT_LL_HANDLE that can be further used in the calls to this module’s APIS.

**SRS_IOTHUB_MQTT_TRANSPORT_07_001: [** If parameter config is `NULL` then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_002: [** If the parameter config's variables `upperConfig` or `waitingToSend` are NULL then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_003: [** If the `upperConfig`'s variables `deviceId`, `iotHubName`, `protocol`, or `iotHubSuffix` are `NULL` then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_004: [** If the `config`'s `waitingToSend` variable is `NULL` then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_005: [** If the `upperConfig`'s variables `deviceKey`, `iotHubName`, or `iotHubSuffix` are empty strings then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_006: [** If the `upperConfig`'s variables `deviceId` is an empty strings or length is greater then 128 then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_007: [** If the `upperConfig`'s variables `protocolGatewayHostName` is `non-Null` and the length is an empty string then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_008: [** If the `upperConfig` contains a valid `protocolGatewayHostName` value the this shall be used for the `hostname`, otherwise the `hostname` shall be constructed using the `iothubname` and `iothubSuffix`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_009: [** If any error is encountered then `IoTHubTransportMqtt_Create` shall return `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_010: [** `IoTHubTransportMqtt_Create` shall allocate memory to save its internal state where all topics, `hostname`, `device_id`, `device_key`, `sasTokenStr` and client handle shall be saved. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_011: [** On Success `IoTHubTransportMqtt_Create` shall return a non-NULL value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_041: [** If both `deviceKey` and `deviceSasToken` fields are `NULL` then `IoTHubTransportMqtt_Create` shall assume a x509 authentication. **]**


### IoTHubTransportMqtt_Destroy

```c
void IoTHubTransportMqtt_Destroy(TRANSPORT_LL_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_012: [**`IoTHubTransportMqtt_Destroy` shall do nothing if parameter handle is `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_014: [**`IoTHubTransportMqtt_Destroy` shall free all the resources currently in use. **]**


### IoTHubTransportMqtt_Register

```c
extern IOTHUB_DEVICE_HANDLE IoTHubTransportMqtt_Register(RANSPORT_LL_HANDLE handle, const IOTHUB_DEVICE_CONFIG* device, PDLIST_ENTRY waitingToSend);
```

This function registers a device with the transport.  The MQTT transport only supports a single device established on create, so this function will prevent multiple devices from being registered.

**SRS_IOTHUB_MQTT_TRANSPORT_17_001: [** `IoTHubTransportMqtt_Register` shall return `NULL` if the `TRANSPORT_LL_HANDLE` is `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_17_002: [** `IoTHubTransportMqtt_Register` shall return `NULL` if `device`, `waitingToSend` are `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_03_001: [** `IoTHubTransportMqtt_Register` shall return `NULL` if `deviceId`, or both `deviceKey` and `deviceSasToken` are `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_03_002: [** `IoTHubTransportMqtt_Register` shall return `NULL` if both `deviceKey` and `deviceSasToken` are provided. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_17_003: [** `IoTHubTransportMqtt_Register` shall return `NULL` if `deviceId` or `deviceKey` do not match the `deviceId` and `deviceKey` passed in during `IoTHubTransportMqtt_Create`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_17_004: [** `IoTHubTransportMqtt_Register` shall return the `TRANSPORT_LL_HANDLE` as the `IOTHUB_DEVICE_HANDLE`. **]**


### IoTHubTransportMqtt_Unregister

```c
extern void IoTHubTransportMqtt_Unregister(IOTHUB_DEVICE_HANDLE deviceHandle);
```

This function is intended to remove a device as registered with the transport.  As there is only one IoT Hub Device per MQTT transport established on create, this function is a placeholder not intended to do meaningful work.

**SRS_IOTHUB_MQTT_TRANSPORT_17_005: [** `IoTHubTransportMqtt_Unregister` shall return. **]**


### IoTHubTransportMqtt_Subscribe_DeviceTwin

```c
int IoTHubTransportMqtt_Subscribe_DeviceTwin(IOTHUB_DEVICE_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_042: [**If the parameter `handle` is `NULL` than `IoTHubTransportMqtt_Subscribe` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_044: [**`IoTHubTransportMqtt_Subscribe_DeviceTwin` shall construct the get state topic string and the notify state topic string. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_046: [**Upon failure `IoTHubTransportMqtt_Subscribe_DeviceTwin` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_047: [**On success `IoTHubTransportMqtt_Subscribe_DeviceTwin` shall return 0. **]**


### IoTHubTransportMqtt_Unsubscribe_DeviceTwin

```c
void IoTHubTransportMqtt_Unsubscribe_DeviceTwin(IOTHUB_DEVICE_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_048: [** If the parameter `handle` is `NULL` than `IoTHubTransportMqtt_Unsubscribe_DeviceTwin` shall do nothing. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_049: [** If `subscribe_state` is set to `IOTHUB_DEVICE_TWIN_DESIRED_STATE` then `IoTHubTransportMqtt_Unsubscribe_DeviceTwin` shall send the get state topic to the mqtt client. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_050: [** If `subscribe_state` is set to `IOTHUB_DEVICE_TWIN_NOTIFICATION_STATE` then `IoTHubTransportMqtt_Unsubscribe_DeviceTwin` shall send the notify state topic to the mqtt client. **]**


### IoTHubTransportMqtt_Subscribe_DeviceMethod

```c
int IoTHubTransportMqtt_Subscribe_DeviceMethod(IOTHUB_DEVICE_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_12_001: [** If the parameter `handle` is `NULL` than `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_002: [** If the MQTT transport has been previously subscribed to DEVICE_METHOD topic `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall do nothing and return 0. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_003: [** `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall set the signaling flag for DEVICE_METHOD topic for the receiver's topic list. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_004: [** `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall construct the DEVICE_METHOD topic string for subscribe. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_005: [** `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall schedule the send of the subscription. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_006: [** Upon failure `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_007: [** On success `IoTHubTransportMqtt_Subscribe_DeviceMethod` shall return 0. **]**


### IoTHubTransportMqtt_Unsubscribe_DeviceMethod

```c
void IoTHubTransportMqtt_Unsubscribe_DeviceMethod(IOTHUB_DEVICE_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_12_008: [** If the parameter `handle` is `NULL` than `IoTHubTransportMqtt_Unsubscribe_DeviceMethod` shall do nothing and return. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_009: [** If the MQTT transport has not been subscribed to DEVICE_METHOD topic `IoTHubTransportMqtt_Unsubscribe_DeviceMethod` shall do nothing and return. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_010: [** `IoTHubTransportMqtt_Unsubscribe_DeviceMethod` shall construct the DEVICE_METHOD topic string for unsubscribe. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_011: [** `IoTHubTransportMqtt_Unsubscribe_DeviceMethod` shall send the unsubscribe. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_12_012: [** `IoTHubTransportMqtt_Unsubscribe_DeviceMethod` shall removes the signaling flag for DEVICE_METHOD topic from the receiver's topic list. **]**


### IoTHubTransportMqtt_Subscribe

```c
int IoTHubTransportMqtt_Subscribe(TRANSPORT_LL_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_015: [** If parameter `handle` is `NULL` than `IoTHubTransportMqtt_Subscribe` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_016: [** `IoTHubTransportMqtt_Subscribe` shall set a flag to enable mqtt_client_subscribe to be called to subscribe to the Message Topic. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_035: [** If current packet state is not CONNACK, DISCONNECT_TYPE, or PACKET_TYPE_ERROR then `IoTHubTransportMqtt_Subscribe` shall set the packet state to `SUBSCRIBE_TYPE`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_017: [** Upon failure `IoTHubTransportMqtt_Subscribe` shall return a non-zero value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_018: [** On success `IoTHubTransportMqtt_Subscribe` shall return 0. **]**


### IoTHubTransportMqtt_Unsubscribe

```c
void IoTHubTransportMqtt_Unsubscribe(TRANSPORT_LL_HANDLE handle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_019: [** If parameter `handle` is `NULL` then `IoTHubTransportMqtt_Unsubscribe` shall do nothing. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_020: [**  `IoTHubTransportMqtt_Unsubscribe` shall call `mqtt_client_unsubscribe` to unsubscribe the mqtt message topic. **]**


### IoTHubTransportMqtt_ProcessItem

```c
IOTHUB_PROCESS_ITEM_RESULT IoTHubTransportMqtt_ProcessItem(TRANSPORT_LL_HANDLE handle, IOTHUB_IDENTITY_TYPE item_type, IOTHUB_IDENTITY_INFO* iothub_item)
```

**SRS_IOTHUBCLIENT_LL_07_001: [** If `handle` or `iothub_item` are `NULL` then `IoTHubTransportMqtt_ProcessItem` shall return `IOTHUB_PROCESS_ERROR`. **]**

**SRS_IOTHUBCLIENT_LL_07_002: [** If the mqtt is not ready to publish messages `IoTHubTransportMqtt_ProcessItem` shall return `IOTHUB_PROCESS_NOT_CONNECTED`. **]**

**SRS_IOTHUBCLIENT_LL_07_003: [** `IoTHubTransportMqtt_ProcessItem` shall publish a message to the mqtt protocol with the message topic for the message type. **]**

**SRS_IOTHUBCLIENT_LL_07_004: [** If any errors are encountered `IoTHubTransportMqtt_ProcessItem` shall return `IOTHUB_PROCESS_ERROR`. **]**

**SRS_IOTHUBCLIENT_LL_07_005: [** If successful `IoTHubTransportMqtt_ProcessItem` shall add mqtt info structure acknowledgement queue. **]**

**SRS_IOTHUBCLIENT_LL_07_006: [** If the `item_type` is not a supported type `IoTHubTransportMqtt_ProcessItem` shall return `IOTHUB_PROCESS_CONTINUE`. **]**


### IoTHubTransportMqtt_DoWork

```c
void IoTHubTransportMqtt_DoWork(TRANSPORT_LL_HANDLE handle, IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_026: [** `IoTHubTransportMqtt_DoWork` shall do nothing if parameter 'handle' and/or**07_055: [**  **]** 'iotHubClientHandle' is `NULL`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_027: [** `IoTHubTransportMqtt_DoWork` shall inspect the 'waitingToSend' `DLIST` passed in config structure. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_028: [** `IoTHubTransportMqtt_DoWork` shall retrieve the payload message from the messageHandle parameter. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_029: [** `IoTHubTransportMqtt_DoWork` shall create a `MQTT_MESSAGE_HANDLE` and pass this to a call to  mqtt_client_publish. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_030: [** `IoTHubTransportMqtt_DoWork` shall call mqtt_client_dowork if it is connected. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_054: [** `IoTHubTransportMqtt_DoWork` shall subscribe to the Notification and get_state Topics if they are defined. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_033: [** `IoTHubTransportMqtt_DoWork` shall iterate through the Waiting Acknowledge messages looking for any message that has been waiting longer than 2 min. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_034: [** If `IoTHubTransportMqtt_DoWork` has previously resent the message two times then it shall fail the message**]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_053: [** `IoTHubTransportMqtt_DoWork` Shall send the mqtt subscribe message if any of the 'MessageTopic', get_state_topic, or notify_state_topic Topics are entered. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_055: [** `IoTHubTransportMqtt_DoWork` shall send a device twin get property message upon successfully retrieving a SUBACK on device twin topics. **]**

### IoTHubTransportMqtt_GetSendStatus

```c
IOTHUB_CLIENT_RESULT IoTHubTransportMqtt_GetSendStatus(TRANSPORT_LL_HANDLE handle, IOTHUB_CLIENT_STATUS *iotHubClientStatus)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_023: [** `IoTHubTransportMqtt_GetSendStatus` shall return `IOTHUB_CLIENT_INVALID_ARG` if called with NULL parameter. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_024: [** `IoTHubTransportMqtt_GetSendStatus` shall return `IOTHUB_CLIENT_OK` and status `IOTHUB_CLIENT_SEND_STATUS_IDLE` if there are currently no event items to be sent or being sent. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_025: [** `IoTHubTransportMqtt_GetSendStatus` shall return `IOTHUB_CLIENT_OK` and status `IOTHUB_CLIENT_SEND_STATUS_BUSY` if there are currently event items to be sent or being sent. **]**


### IoTHubTransportMqtt_SetOption

```c
IOTHUB_CLIENT_RESULT IoTHubTransportMqtt_SetOption(TRANSPORT_LL_HANDLE handle, const char* optionName, const void* value)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_021: [** If any parameter is `NULL` then `IoTHubTransportMqtt_SetOption` shall return `IOTHUB_CLIENT_INVALID_ARG`. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_031: [** If the `optionName` parameter is set to `logtrace` then the value shall be a bool_ptr and the value will determine if the mqtt client log is on or off. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_032: [** IoTHubTransportMqtt_SetOption shall pass down the option to xio_setoption if the option parameter is not a known option string for the MQTT transport. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_036: [** If the `optionName` parameter is set to "keepalive" then the value shall be a int_ptr and the value will determine the mqtt keepalive time that is set for pings. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_037: [** If the `optionName` parameter is set to supplied int_ptr keepalive is the same value as the existing keepalive then `IoTHubTransportMqtt_SetOption` shall do nothing. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_038: [** If the client is connected when the keepalive is set then `IoTHubTransportMqtt_SetOption` shall disconnect and reconnect with the specified keepalive value. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_039: [** If the `optionName` parameter is set to `x509certificate` then the value shall be a const char pointer of the certificate to be used for x509. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_07_040: [** If the `optionName` parameter is set to `x509privatekey` then the value shall be a const char of the RSA Private Key to be used for x509. **]**


### IoTHubTransportMqtt_GetHostname
```c
STRING_HANDLE IoTHubTransportMqtt_GetHostname(TRANSPORT_LL_HANDLE handle)
```

IoTHubTransportMqtt_GetHostname returns a STRING_HANDLE for the hostname.

**SRS_IOTHUB_MQTT_TRANSPORT_02_001: [** If `handle` is `NULL` then `IoTHubTransportMqtt_GetHostname` shall fail and return NULL. **]**

**SRS_IOTHUB_MQTT_TRANSPORT_02_002: [** Otherwise `IoTHubTransportMqtt_GetHostname` shall return a `non-NULL` `STRING_HANDLE` containg the hostname. **]**


### MQTT_Protocol

```c
const TRANSPORT_PROVIDER* MQTT_Protocol(void)
```

**SRS_IOTHUB_MQTT_TRANSPORT_07_022: [**This function shall return a pointer to a structure of type TRANSPORT_PROVIDER having the following values for it's fields:

IoTHubTransport_Subscribe_DeviceMethod = IoTHubTransportMqtt_Subscribe_DeviceMethod
IoTHubTransport_Unsubscribe_DeviceMethod = IoTHubTransportMqtt_Unsubscribe_DeviceMethod
IoTHubTransport_Subscribe_DeviceTwin = IoTHubTransportMqtt_Subscribe_DeviceTwin
IoTHubTransport_Unsubscribe_DeviceTwin = IoTHubTransportMqtt_Unsubscribe_DeviceTwin
IoTHubTransport_ProcessItem - IoTHubTransportMqtt_ProcessItem
IoTHubTransport_GetHostname = IoTHubTransportMqtt_GetHostname
IoTHubTransport_Create = IoTHubTransportMqtt_Create
IoTHubTransport_Destroy = IoTHubTransportMqtt_Destroy
IoTHubTransport_Subscribe = IoTHubTransportMqtt_Subscribe
IoTHubTransport_Unsubscribe = IoTHubTransportMqtt_Unsubscribe
IoTHubTransport_DoWork = IoTHubTransportMqtt_DoWork
IoTHubTransport_SetOption = IoTHubTransportMqtt_SetOption**]**
