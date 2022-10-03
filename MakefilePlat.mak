#    SPDX-License-Identifier: GPL-3.0-or-later
#    Copyright © 1991-2022 Amebis
#    Copyright © 2016 GÉANT

CleanSetup ::
	-if exist "output\Setup\WLANManager$(PLAT_SUFFIX).exe" del /f /q "output\Setup\WLANManager$(PLAT_SUFFIX).exe"
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Clean /p:Platform=$(PLAT) /p:Configuration=Release
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Clean /p:Platform=$(PLAT) /p:Configuration=Debug


######################################################################
# Setup
######################################################################

Setup :: \
	"output\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX).msi" \
	"output\Setup\WLANManager$(PLAT_SUFFIX).exe"

SetupDebug :: \
	"output\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)D.msi"

SetupCompile ::
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Build /p:Platform=$(PLAT) /p:Configuration=Release

SetupDebugCompile ::
	msbuild.exe $(MSBUILDFLAGS) "$(MSIBUILD_PRODUCT_NAME_ID).sln" /t:Build /p:Platform=$(PLAT) /p:Configuration=Debug

"output\Setup\PDB.zip" : output\$(PLAT).Release\*.pdb


######################################################################
# File copy
######################################################################

"output\Setup\WLANManager$(PLAT_SUFFIX).exe" : "output\$(PLAT).Release\WLANManager.exe"
	copy /y $** $@ > NUL


######################################################################
# Configuration Specific
######################################################################

CFG=Release
CFG_SUFFIX=
!INCLUDE "MakefilePlatCfg.mak"

CFG=Debug
CFG_SUFFIX=D
!INCLUDE "MakefilePlatCfg.mak"
