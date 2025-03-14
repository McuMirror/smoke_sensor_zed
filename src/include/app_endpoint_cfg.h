#ifndef SRC_INCLUDE_APP_ENDPOINT_CFG_H_
#define SRC_INCLUDE_APP_ENDPOINT_CFG_H_

#define APP_ENDPOINT1 0x01
#define APP_ENDPOINT2 0x02
#define APP_ENDPOINT3 0x03
#define APP_ENDPOINT4 0x04
#define APP_ENDPOINT5 0x05

#ifndef ZCL_ON_OFF_SWITCH_CFG
#define ZCL_ON_OFF_SWITCH_CFG
#endif

/**
 *  @brief Defined for basic cluster attributes
 */
typedef struct{
    uint8_t  zclVersion;
    uint8_t  appVersion;
    uint8_t  stackVersion;
    uint8_t  hwVersion;
    uint8_t  manuName[ZCL_BASIC_MAX_LENGTH];
    uint8_t  modelId[ZCL_BASIC_MAX_LENGTH];
    uint8_t  dateCode[ZCL_BASIC_MAX_LENGTH];
    uint8_t  powerSource;
    uint8_t  genDevClass;                        //attr 8
    uint8_t  genDevType;                         //attr 9
    uint8_t  deviceEnable;
    uint8_t  swBuildId[ZCL_BASIC_MAX_LENGTH];    //attr 4000
} zcl_basicAttr_t;

/**
 *  @brief Defined for identify cluster attributes
 */
typedef struct{
    uint16_t identifyTime;
}zcl_identifyAttr_t;

/**
 *  @brief Defined for power configuration cluster attributes
 */
typedef struct{
    uint8_t  batteryVoltage;      //0x20
    uint8_t  batteryPercentage;   //0x21
}zcl_powerAttr_t;

/**
 *  @brief Defined for ias zone cluster attributes
 */
typedef struct {
    uint8_t     zoneState;
    uint16_t    zoneType;
    uint16_t    zoneStatus;
    extAddr_t   iasCieAddr;
    uint8_t     zoneId;
} zcl_iasZoneAttr_t;


/**
 *  @brief  Defined for poll control cluster attributes
 */
typedef struct {
    uint32_t chkInInterval;
    uint32_t longPollInterval;
    uint32_t chkInIntervalMin;
    uint32_t longPollIntervalMin;
    uint16_t shortPollInterval;
    uint16_t fastPollTimeout;
    uint16_t fastPollTimeoutMax;
} zcl_pollCtrlAttr_t;

typedef struct {
    u8 switchType;
    u8 switchActions;
} zcl_onOffSwitchCfg_t;


extern uint8_t APP_EP1_CB_CLUSTER_NUM;

/* Attributes */
extern zcl_basicAttr_t g_zcl_basicAttrs;
extern zcl_identifyAttr_t g_zcl_identifyAttrs;
extern zcl_pollCtrlAttr_t g_zcl_pollCtrlAttrs;
//extern zcl_appAttr_t g_zcl_appAttrs;
//extern zcl_appCfgAttr_t g_zcl_appCfgAttrs;
extern zcl_iasZoneAttr_t g_zcl_iasZoneAttrs;

#define zcl_iasZoneAttrGet()    &g_zcl_iasZoneAttrs
#define zcl_pollCtrlAttrGet()   &g_zcl_pollCtrlAttrs

nv_sts_t zcl_onOffCfgAttr_save(void);
nv_sts_t zcl_onOffCfgAttr_restore(void);


#endif /* SRC_INCLUDE_APP_ENDPOINT_CFG_H_ */
