# MenuDog

Data Flow:

- User -> Navigator -> Editor -> Quarantine
- Monitor -> Editor -> Quarantine

# User

System requirement of user machine is Windows 10 or later due to limitation of Qt6.

# Navigator

- Elementary: Built-in navigator, a simple simulator of Windows Explorer.
- Intermediate: Specify path of file/folder. Support CLSID for special folders.
- Advanced: Feel free to trigger context menu in the REAL WORLD supported by
  DLL injection technique which may be complained by security softwares.

# Editor

- Legacy: Support legacy context menu which has been existing for decades.
- Modern: Flourish (but inefficient) context menu introduced and supported by
  Windows 11(by now).

# Quarantine

Log any writing operation for your any regretion.

# Monitor

A benign daemon.
