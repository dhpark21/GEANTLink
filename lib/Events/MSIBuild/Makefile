#
#    Copyright 1991-2016 Amebis
#    Copyright 2016 GÉANT
#
#    This file is part of GÉANTLink.
#
#    GÉANTLink is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    GÉANTLink is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with GÉANTLink. If not, see <http://www.gnu.org/licenses/>.
#

!INCLUDE "..\..\..\include\MSIBuildCfg.mak"

!IFNDEF MSIBUILD_PRODUCT_NAME
!ERROR Parameter MSIBUILD_PRODUCT_NAME is undefined.
!ENDIF

!IFNDEF MSIBUILD_PRODUCT_NAME_UC
!ERROR Parameter MSIBUILD_PRODUCT_NAME_UC is undefined.
!ENDIF


######################################################################
# AppSearch

All :: "$(LANG).$(PLAT).$(CFG).AppSearch-1.idt"

"$(LANG).$(PLAT).$(CFG).AppSearch-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Property	Signature_
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)
AppSearch	Property	Signature_
OLD$(MSIBUILD_PRODUCT_NAME_UC)DIR	clEvents.dll.$(PLAT)
<<NOKEEP


######################################################################
# CompLocator

All :: "$(LANG).$(PLAT).$(CFG).CompLocator-1.idt"

"$(LANG).$(PLAT).$(CFG).CompLocator-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Signature_	ComponentId	Type
s$(MSIBUILD_LENGTH_ID)	s38	I2
CompLocator	Signature_
!IF "$(PLAT)" == "Win32"
clEvents.dll.Win32	{E691777F-2A7F-4E8D-9B0A-499075499649}	1
!ENDIF
!IF "$(PLAT)" == "x64"
clEvents.dll.x64	{F5ACC467-0AE2-48B4-B1AB-0B87E96AE737}	1
!ENDIF
<<NOKEEP


######################################################################
# Component

All :: "$(LANG).$(PLAT).$(CFG).Component-1.idt"

"$(LANG).$(PLAT).$(CFG).Component-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Component	ComponentId	Directory_	Attributes	Condition	KeyPath
s$(MSIBUILD_LENGTH_ID)	S38	s$(MSIBUILD_LENGTH_ID)	i2	S255	S$(MSIBUILD_LENGTH_ID)
Component	Component
!IF "$(PLAT)" == "Win32"
compEvents.dll.Win32	{E691777F-2A7F-4E8D-9B0A-499075499649}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	0		fileEvents.dll.Win32
!ENDIF
!IF "$(PLAT)" == "x64"
compEvents.dll.x64	{F5ACC467-0AE2-48B4-B1AB-0B87E96AE737}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	256		fileEvents.dll.x64
!ENDIF
compEvents1	{CE799218-FEF2-4584-80D1-751BEAECC4F3}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEvents1
compEvents2	{CE8D096D-54A9-4F6C-8B2B-BCE8253126DC}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEvents2
compEvents3	{68706D4D-4AD5-48E0-9C23-EE351E9A6FAA}	$(MSIBUILD_PRODUCT_NAME_UC)BINDIR	$(MSIBUILD_COMPONENT_ATTRIB_REGISTRY)		regEvents3
<<NOKEEP


######################################################################
# File

All :: "$(LANG).$(PLAT).$(CFG).File-1.idt"

"$(LANG).$(PLAT).$(CFG).File-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
File	Component_	FileName	FileSize	Version	Language	Attributes	Sequence
s$(MSIBUILD_LENGTH_ID)	s$(MSIBUILD_LENGTH_ID)	l255	i4	S$(MSIBUILD_LENGTH_ID)	S20	I2	i2
File	File
fileEvents.dll.$(PLAT)	compEvents.dll.$(PLAT)	EAPMET~1.DLL|Events.dll	0		0	1536	1
<<NOKEEP


######################################################################
# Registry

All :: "$(LANG).$(PLAT).$(CFG).Registry-1.idt"

"$(LANG).$(PLAT).$(CFG).Registry-1.idt" : "Makefile" "..\..\..\include\MSIBuildCfg.mak"
	-if exist $@ del /f /q $@
	move /y << $@ > NUL
Registry	Root	Key	Name	Value	Component_
s$(MSIBUILD_LENGTH_ID)	i2	l255	L255	L0	s$(MSIBUILD_LENGTH_ID)
Registry	Registry
regEvents1	2	SOFTWARE\Microsoft\Windows\CurrentVersion\WINEVT\Publishers\{3f65af01-ce8f-4c7d-990b-673b244aac7b}		$(MSIBUILD_PRODUCT_NAME)-Events	compEvents1
regEvents2	2	SOFTWARE\Microsoft\Windows\CurrentVersion\WINEVT\Publishers\{3f65af01-ce8f-4c7d-990b-673b244aac7b}	MessageFileName	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]Events.dll	compEvents2
regEvents3	2	SOFTWARE\Microsoft\Windows\CurrentVersion\WINEVT\Publishers\{3f65af01-ce8f-4c7d-990b-673b244aac7b}	ResourceFileName	[$(MSIBUILD_PRODUCT_NAME_UC)BINDIR]Events.dll	compEvents3
<<NOKEEP


######################################################################
# Build MSM module!
######################################################################

!INCLUDE "..\..\..\MSI\MSIBuild\MSM.mak"
