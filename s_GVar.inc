																																													/*
=====================================================================
GVar - GVar Include
=====================================================================
Developer: Snir Sofer.
=====================================================================
Legal:
	* This Source Code Form is subject to the terms of the Mozilla Public
	* License, v. 2.0. If a copy of the MPL was not distributed with this
	* file, You can obtain one at http://mozilla.org/MPL/2.0/.
=====================================================================
Function List:

	native SetGVarInt(GVarName[],GVarValue);
	native GetGVarInt(GVarName[]);
	native SetGVarFloat(GVarName[],Float:GVarValue);
	native Float:GetGVarFloat(GVarName[]);
	native SetGVarString(GVarName[],GVarValue[])
	native GetGVarString(GVarName[],GVarValue[],maxsize = sizeof(GVarValue),bool:unpack = true);
	native DeleteGVar(GVarName[]);
	native IsSetGVar(GVarName[]);

																																													*/
#define MAX_GVAR_STRINGS 20000000
#define ABSTRACT_MACHINE 0
#define SetGVarInt(%0,%1) setproperty(ABSTRACT_MACHINE, %0, %1)
#define GetGVarInt(%0) getproperty(ABSTRACT_MACHINE,%0)
#define SetGVarFloat(%0,Float:%1) setproperty(ABSTRACT_MACHINE,%0,_:%1)
#define Float:GetGVarFloat(%0) Float:getproperty(ABSTRACT_MACHINE,%0)
#define IsSetGVar(%0) existproperty(ABSTRACT_MACHINE,%0)

stock SetGVarString(GVarName[],GVarValue[])
{
    if(existproperty(0,GVarName))
        return setproperty(ABSTRACT_MACHINE,_,getproperty(ABSTRACT_MACHINE,GVarName)+MAX_GVAR_STRINGS,GVarValue);
    else
    {
        static index = MAX_GVAR_STRINGS * 2;
        setproperty(ABSTRACT_MACHINE,_,++index,GVarValue );
        return setproperty(ABSTRACT_MACHINE,GVarName,index-MAX_GVAR_STRINGS);
    }
}
stock GetGVarString(GVarName[],GVarValue[],maxsize = sizeof(GVarValue),bool:unpack = true)
{
    getproperty(ABSTRACT_MACHINE, _, getproperty(ABSTRACT_MACHINE,GVarName) + MAX_GVAR_STRINGS, GVarValue );
    if(unpack )strunpack(GVarValue,GVarValue,maxsize);
    return getproperty(ABSTRACT_MACHINE,GVarName);
}
stock DeleteGVar(GVarName[])
{
    if(existproperty(ABSTRACT_MACHINE,GVarName))\
        deleteproperty(ABSTRACT_MACHINE,_,getproperty(ABSTRACT_MACHINE,GVarName)+MAX_GVAR_STRINGS);
    return deleteproperty(ABSTRACT_MACHINE,GVarName);
}
#undef MAX_GVAR_STRINGS
#undef ABSTRACT_MACHINE
