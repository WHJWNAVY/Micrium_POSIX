/*
*********************************************************************************************************
*                                              uC/Shell
*                                            Shell utility
*
*                    Copyright 2007-2020 Silicon Laboratories Inc. www.silabs.com
*
*                                 SPDX-License-Identifier: APACHE-2.0
*
*               This software is subject to an open source license and is distributed by
*                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
*                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
*
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*
*                                         GENERAL SHELL COMMANDS
*
* Filename : sh_shell.c
* Version  : V1.04.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   SH_SHELL_MODULE
#include <sh_shell.h>


/*
*********************************************************************************************************
*                                              LOCAL DEFINES
*********************************************************************************************************
*/

#define  SH_SHELL_NEW_LINE                      (CPU_CHAR *)"\r\n"
#define  SH_SHELL_BLANK_LINE                    (CPU_CHAR *)"\r\n\r\n"
#define  SH_SHELL_STR_HELP                      (CPU_CHAR *)"-h"

/*
*********************************************************************************************************
*                                        ARGUMENT ERROR MESSAGES
*********************************************************************************************************
*/

#define  SH_SHELL_ARG_ERR_HELP                  (CPU_CHAR *)"Sh_help: usage: Sh_help\r\n                Sh_help [command]"
#define  SH_SHELL_ARG_ERR_VERSION               (CPU_CHAR *)"Sh_version: usage: Sh_version"

/*
*********************************************************************************************************
*                                      COMMAND EXPLANATION MESSAGES
*********************************************************************************************************
*/

#define  SH_SHELL_CMD_EXP_HELP                  (CPU_CHAR *)"                Get list of commands, or information about a command."
#define  SH_SHELL_CMD_EXP_VERSION               (CPU_CHAR *)"                   Get list of all components version."

/*
*********************************************************************************************************
*                                             LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                        LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


static  CPU_INT16S  ShShell_help(CPU_INT16U        argc,
                                 CPU_CHAR         *argv[],
                                 SHELL_OUT_FNCT    out_fnct,
                                 SHELL_CMD_PARAM  *pcmd_param);

static  CPU_INT16S  ShShell_version(CPU_INT16U        argc,
                                   CPU_CHAR         *argv[],
                                   SHELL_OUT_FNCT    out_fnct,
                                   SHELL_CMD_PARAM  *pcmd_param);

static  SHELL_CMD  ShShell_CmdTbl [] =
{
    {"Sh_help",    ShShell_help},
    {"Sh_version", ShShell_version},
    {0,         0           }
};


/*
*********************************************************************************************************
*                                       LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             ShShell_Init()
*
* Description : Initialize Shell for general shell commands.
*
* Argument(s) : none.
*
* Return(s)   : DEF_OK,   if general shell commands were added.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  ShShell_Init (void)
{
    SHELL_ERR    err;
    CPU_BOOLEAN  ok;


    Shell_CmdTblAdd((CPU_CHAR *)"Sh", ShShell_CmdTbl, &err);

    ok = (err == SHELL_ERR_NONE) ? DEF_OK : DEF_FAIL;
    return (ok);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           COMMAND FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             ShShell_help()
*
* Description : List all commands or invoke '--help' for another command.
*
* Argument(s) : argc            The number of arguments.
*
*               argv            Array of arguments.
*
*               out_fnct        The output function.
*
*               pcmd_param      Pointer to the command parameters.
*
* Return(s)   : SHELL_EXEC_ERR, if an error is encountered.
*               SHELL_ERR_NONE, otherwise.
*
* Caller(s)   : Shell, in response to command execution.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT16S  ShShell_help (CPU_INT16U        argc,
                                  CPU_CHAR         *argv[],
                                  SHELL_OUT_FNCT    out_fnct,
                                  SHELL_CMD_PARAM  *pcmd_param)
{
    CPU_CHAR           cmd_str[SHELL_CFG_MODULE_CMD_NAME_LEN_MAX + 4];
    SHELL_ERR          err;
    SHELL_CMD         *pcmd;
    SHELL_MODULE_CMD  *pmodule_cmd;


    if (argc == 2) {
        if (Str_Cmp(argv[1], SH_SHELL_STR_HELP) == 0) {
            (void)out_fnct(SH_SHELL_ARG_ERR_HELP, (CPU_INT16U)Str_Len(SH_SHELL_ARG_ERR_HELP), pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_NEW_LINE,     2,                                          pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_CMD_EXP_HELP, (CPU_INT16U)Str_Len(SH_SHELL_CMD_EXP_HELP), pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_NEW_LINE,     2,                                          pcmd_param->pout_opt);
            return (SHELL_ERR_NONE);
        }
    }

    if ((argc != 1) && (argc != 2)) {
        (void)out_fnct(SH_SHELL_ARG_ERR_HELP, (CPU_INT16U)Str_Len(SH_SHELL_ARG_ERR_HELP), pcmd_param->pout_opt);
        (void)out_fnct(SH_SHELL_NEW_LINE,     2,                                          pcmd_param->pout_opt);
        return (SHELL_EXEC_ERR);
    }

    switch (argc) {
        case 1:
             pmodule_cmd = Shell_ModuleCmdUsedPoolPtr;
             while (pmodule_cmd != (SHELL_MODULE_CMD *)0) {
                 pcmd = pmodule_cmd->CmdTblPtr;
                 if (pcmd != (SHELL_CMD *)0) {
                     while (pcmd->Fnct != (SHELL_CMD_FNCT)0) {
                         (void)out_fnct((CPU_CHAR *)pcmd->Name,
                                        (CPU_INT16U)Str_Len(pcmd->Name),
                                                    pcmd_param->pout_opt);
                         (void)out_fnct(SH_SHELL_NEW_LINE, 2,                               pcmd_param->pout_opt);
                         pcmd++;
                     }
                 }
                 pmodule_cmd = pmodule_cmd->NextModuleCmdPtr;
             }
             break;

        case 2:
             Str_Copy(cmd_str, argv[1]);
             Str_Cat(cmd_str, (CPU_CHAR *)" ");
             Str_Cat(cmd_str, SH_SHELL_STR_HELP);

             Shell_Exec(cmd_str, out_fnct, pcmd_param, &err);

             switch (err) {
                case SHELL_ERR_CMD_NOT_FOUND:
                case SHELL_ERR_CMD_SEARCH:
                case SHELL_ERR_ARG_TBL_FULL:
                     (void)out_fnct((CPU_CHAR *)"Command not recognized: ", 25,                           pcmd_param->pout_opt);
                     (void)out_fnct(argv[1],                                (CPU_INT16U)Str_Len(argv[1]), pcmd_param->pout_opt);
                     (void)out_fnct(SH_SHELL_NEW_LINE,                      2,                            pcmd_param->pout_opt);
                     break;

                case SHELL_ERR_NONE:
                case SHELL_ERR_NULL_PTR:
                case SHELL_ERR_CMD_EXEC:
                default:
                     break;
             }
             break;

        default:
             break;
    }

    return (SHELL_ERR_NONE);
}

typedef struct {
    CPU_CHAR* component;
    CPU_CHAR* version;
} sh_version_t;

static const sh_version_t SH_VERSIONS[] = {
    {
        .component = "uCOS-III",
        .version = OS_VERSION_STRING,
    },
    {
        .component = "uC-CPU",
        .version = CPU_CORE_VERSION_STRING,
    },
    {
        .component = "uC-LIB",
        .version = LIB_VERSION_STRING,
    },
    {
        .component = "uC-Shell",
        .version = SHELL_VERSION_STRING,
    },
    {
        .component = "uC-Terminal",
        .version = TERMINAL_VERSION_STRING,
    }
};

#define SH_OUT_FMT_DELIMETER " : "
#define SH_OUT_FMT_VERSIONS "Components : Versions\r\n-------------------------"

static  CPU_INT16S  ShShell_version (CPU_INT16U        argc,
                                  CPU_CHAR         *argv[],
                                  SHELL_OUT_FNCT    out_fnct,
                                  SHELL_CMD_PARAM  *pcmd_param)
{
    CPU_INT16U         veri = 0;
    sh_version_t      *vert = NULL;

    if (argc == 2) {
        if (Str_Cmp(argv[1], SH_SHELL_STR_HELP) == 0) { // -h
            (void)out_fnct(SH_SHELL_ARG_ERR_VERSION, (CPU_INT16U)Str_Len(SH_SHELL_ARG_ERR_VERSION), pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_NEW_LINE,        (CPU_INT16U)Str_Len(SH_SHELL_NEW_LINE),        pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_CMD_EXP_VERSION, (CPU_INT16U)Str_Len(SH_SHELL_CMD_EXP_VERSION), pcmd_param->pout_opt);
            (void)out_fnct(SH_SHELL_NEW_LINE,        (CPU_INT16U)Str_Len(SH_SHELL_NEW_LINE),        pcmd_param->pout_opt);
            return (SHELL_ERR_NONE);
        }
    }

    if ((argc != 1) && (argc != 2)) {
        (void)out_fnct(SH_SHELL_ARG_ERR_VERSION, (CPU_INT16U)Str_Len(SH_SHELL_ARG_ERR_VERSION), pcmd_param->pout_opt);
        (void)out_fnct(SH_SHELL_NEW_LINE,        (CPU_INT16U)Str_Len(SH_SHELL_NEW_LINE),        pcmd_param->pout_opt);
        return (SHELL_EXEC_ERR);
    }

    (void)out_fnct(SH_OUT_FMT_VERSIONS, (CPU_INT16U)Str_Len(SH_OUT_FMT_VERSIONS), pcmd_param->pout_opt);
    (void)out_fnct(SH_SHELL_NEW_LINE,   (CPU_INT16U)Str_Len(SH_SHELL_NEW_LINE),   pcmd_param->pout_opt);

    for(veri=0; veri<(sizeof(SH_VERSIONS)/sizeof(sh_version_t)); veri++) {
        vert = &(SH_VERSIONS[veri]);
        (void)out_fnct(vert->component,       (CPU_INT16U)Str_Len(vert->component),       pcmd_param->pout_opt);
        (void)out_fnct(SH_OUT_FMT_DELIMETER,  (CPU_INT16U)Str_Len(SH_OUT_FMT_DELIMETER),  pcmd_param->pout_opt);
        (void)out_fnct(vert->version,         (CPU_INT16U)Str_Len(vert->version),         pcmd_param->pout_opt);
        (void)out_fnct(SH_SHELL_NEW_LINE,     (CPU_INT16U)Str_Len(SH_SHELL_NEW_LINE),     pcmd_param->pout_opt);
    }

    return (SHELL_ERR_NONE);
}
