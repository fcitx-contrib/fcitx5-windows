Start-Process -Verb RunAs powershell.exe -Args "-executionpolicy bypass -command Set-Location \`"$PWD\`"; regsvr32 build/dll/fcitx5-x86_64.dll"
