/////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 1998 Telic Software International B.V.
//
// Module Name:
//
//    NTServiceEventLogMsg.h
//
// Abstract:
//
//    Messages for Event Logging for the service
//
//
//Notes:
//	   DO NOT EDIT THIS FILE BY HAND!
//
//    This file is GENERATED by the MC tool from the NTServiceEventLogMsg.mc file.
//
//////////////////////////////////////////////////////////////////////////


#ifndef NTSERVICEEVENTLOGMSG_H
#define NTSERVICEEVENTLOGMSG_H

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MSG_INFO_1
//
// MessageText:
//
//  %1
//
#define MSG_INFO_1                       ((DWORD)0x40000000L)

//
// MessageId: MSG_WARNING_1
//
// MessageText:
//
//  %1
//
#define MSG_WARNING_1                    ((DWORD)0x80000001L)

//
// MessageId: MSG_ERROR_1
//
// MessageText:
//
//  %1
//
#define MSG_ERROR_1                      ((DWORD)0xC0000002L)

//
// MessageId: MSG_SUCCESS_1
//
// MessageText:
//
//  %1
//
#define MSG_SUCCESS_1                    ((DWORD)0x00000003L)

#endif