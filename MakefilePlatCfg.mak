#    SPDX-License-Identifier: GPL-3.0-or-later
#    Copyright © 1991-2022 Amebis
#    Copyright © 2016 GÉANT

CleanSetup ::
	-if exist "output\$(PLAT).$(CFG).ddf" del /f /q "output\$(PLAT).$(CFG).ddf"
	-if exist "output\$(PLAT).$(CFG).cab" del /f /q "output\$(PLAT).$(CFG).cab"
	-if exist "output\$(PLAT).$(CFG).inf" del /f /q "output\$(PLAT).$(CFG).inf"
	-if exist "output\$(PLAT).$(CFG).rpt" del /f /q "output\$(PLAT).$(CFG).rpt"
	-if exist "output\$(PLAT).$(CFG).msi" del /f /q "output\$(PLAT).$(CFG).msi"
	-if exist "output\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" del /f /q "output\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi"


######################################################################
# Building
######################################################################

"output\$(PLAT).$(CFG).ddf" : \
	"output\ca_ES.$(PLAT).$(CFG).2.msi" \
	"output\de_DE.$(PLAT).$(CFG).2.msi" \
	"output\el_GR.$(PLAT).$(CFG).2.msi" \
	"output\es_ES.$(PLAT).$(CFG).2.msi" \
	"output\et_EE.$(PLAT).$(CFG).2.msi" \
	"output\hr_HR.$(PLAT).$(CFG).2.msi" \
	"output\hu_HU.$(PLAT).$(CFG).2.msi" \
	"output\it_IT.$(PLAT).$(CFG).2.msi" \
	"output\nb_NO.$(PLAT).$(CFG).2.msi" \
	"output\pl_PL.$(PLAT).$(CFG).2.msi" \
	"output\pt_PT.$(PLAT).$(CFG).2.msi" \
	"output\ro_RO.$(PLAT).$(CFG).2.msi" \
	"output\sl_SI.$(PLAT).$(CFG).2.msi" \
	"output\sr_RS.$(PLAT).$(CFG).2.msi" \
	"output\tr_TR.$(PLAT).$(CFG).2.msi" \
	"output\en_US.$(PLAT).$(CFG).2.msi"
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:MakeDDF //Nologo "$(@:"=).tmp" $** /O:"output\$(PLAT).$(CFG)" /C:LZX
	move /y "$(@:"=).tmp" $@ > NUL

"output\$(PLAT).$(CFG).cab" \
"output\$(PLAT).$(CFG).inf" \
"output\$(PLAT).$(CFG).rpt" : "output\$(PLAT).$(CFG).ddf"
	makecab.exe /F $**

"output\$(PLAT).$(CFG).msi" : \
	"output\ca_ES.$(PLAT).$(CFG).mst" \
	"output\de_DE.$(PLAT).$(CFG).mst" \
	"output\el_GR.$(PLAT).$(CFG).mst" \
	"output\es_ES.$(PLAT).$(CFG).mst" \
	"output\et_EE.$(PLAT).$(CFG).mst" \
	"output\hr_HR.$(PLAT).$(CFG).mst" \
	"output\hu_HU.$(PLAT).$(CFG).mst" \
	"output\it_IT.$(PLAT).$(CFG).mst" \
	"output\nb_NO.$(PLAT).$(CFG).mst" \
	"output\pl_PL.$(PLAT).$(CFG).mst" \
	"output\pt_PT.$(PLAT).$(CFG).mst" \
	"output\ro_RO.$(PLAT).$(CFG).mst" \
	"output\sl_SI.$(PLAT).$(CFG).mst" \
	"output\sr_RS.$(PLAT).$(CFG).mst" \
	"output\tr_TR.$(PLAT).$(CFG).mst" \
	"output\en_US.$(PLAT).$(CFG).msi"
	-if exist $@ del /f /q $@
	-if exist "$(@:"=).tmp" del /f /q "$(@:"=).tmp"
	copy /y "output\en_US.$(PLAT).$(CFG).msi" "$(@:"=).tmp" > NUL
	attrib.exe -r "$(@:"=).tmp"
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\ca_ES.$(PLAT).$(CFG).mst" 1027 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\de_DE.$(PLAT).$(CFG).mst" 1031 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\el_GR.$(PLAT).$(CFG).mst" 1032 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\es_ES.$(PLAT).$(CFG).mst" 1034 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\et_EE.$(PLAT).$(CFG).mst" 1061 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\hr_HR.$(PLAT).$(CFG).mst" 1050 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\hu_HU.$(PLAT).$(CFG).mst" 1038 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\it_IT.$(PLAT).$(CFG).mst" 1040 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\nb_NO.$(PLAT).$(CFG).mst" 1044 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\pl_PL.$(PLAT).$(CFG).mst" 1045 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\pt_PT.$(PLAT).$(CFG).mst" 2070 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\ro_RO.$(PLAT).$(CFG).mst" 1048 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\sl_SI.$(PLAT).$(CFG).mst" 1060 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\sr_RS.$(PLAT).$(CFG).mst" 2074 /L
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:AddStorage //Nologo "$(@:"=).tmp" "output\tr_TR.$(PLAT).$(CFG).mst" 1055 /L
	move /y "$(@:"=).tmp" $@ > NUL

"output\Setup\$(MSIBUILD_PRODUCT_NAME_ID)$(PLAT_SUFFIX)$(CFG_SUFFIX).msi" : \
	"output\$(PLAT).$(CFG).msi" \
	"output\$(PLAT).$(CFG).cab" \
	"output\$(PLAT).$(CFG).inf"
	-if exist $@ del /f /q $@
	copy /y "output\$(PLAT).$(CFG).msi" "$(@:"=).tmp" > NUL
	cscript.exe "MSI\MSIBuild\MSI.wsf" //Job:SetCAB //Nologo "$(@:"=).tmp" "output\$(PLAT).$(CFG).inf" /E
	"$(WINDOWSSDKVERBINPATH)x86\msiinfo.exe" "$(@:"=).tmp" /nologo /U 4
!IF DEFINED(MANIFESTCERTIFICATETHUMBPRINT)
	signtool.exe sign /sha1 "$(MANIFESTCERTIFICATETHUMBPRINT)" /fd sha256 /tr "$(MANIFESTTIMESTAMPRFC3161URL)" /td sha256 /d "$(MSIBUILD_PRODUCT_NAME)" /q "$(@:"=).tmp"
!ELSEIF EXISTS("$(APPDATA)\Microsoft.Trusted.Signing.Client.json")
	signtool.exe sign /dlib "$(USERPROFILE)\.nuget\packages\microsoft.trusted.signing.client\1.0.53\bin\x64\Azure.CodeSigning.Dlib.dll" /dmdf "$(APPDATA)\Microsoft.Trusted.Signing.Client.json" /fd sha256 /tr "http://timestamp.acs.microsoft.com" /td sha256 /d "$(MSIBUILD_PRODUCT_NAME)" /q "$(@:"=).tmp"
!ENDIF
	attrib.exe +r "$(@:"=).tmp"
	move /y "$(@:"=).tmp" $@ > NUL

