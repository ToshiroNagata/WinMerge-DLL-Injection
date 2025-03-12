# WinMerge-DLL-Injection
PoC for DLL Injection in WinMerge 2.16.46 (64-bit) allowing arbitrary code execution.

---

## 🎯 Description
A DLL Injection vulnerability exists in **WinMerge 2.16.46 (64-bit)** due to unsafe DLL search order handling.  
When `WinMerge.exe` is executed, it attempts to load `icu.dll` from the installation directory (`C:\Program Files\WinMerge`).  
If an attacker places a malicious `icu.dll` in the same directory, WinMerge will execute the DLL under the context of the current user, allowing **arbitrary code execution**.  

---

## 🛠️ Technical Details
- **Product:** WinMerge  
- **Version:** 2.16.46  
- **Architecture:** 64-bit  
- **Vulnerability Type:** Unsafe DLL Search Order → DLL Injection  
- **Impact:** Code Execution  
- **Attack Type:** Local  

---

## 📂 Files
| File | Description |
|------|-------------|
| `icu.c` | Source code of the malicious DLL |
| `icu.dll` | Compiled version of the malicious DLL |

---

## 🚨 Proof of Concept (PoC)

### 1. Compile the DLL
#### ✅ Using **MinGW**:
 x86_64-w64-mingw32-gcc -shared -o icu.dll icu.c -Wall
 
#### ✅ Using Visual Studio:
 cl /LD icu.c /o icu.dll

### 2. Place the DLL
Copy icu.dll to: C:\Program Files\WinMerge\

### 3. Execute the attack

3.1 Open WinMerge.exe

3.2 Upon execution:

  - ✅ calc.exe will launch → Confirms successful code execution
    
  - ✅ A file privilege_test.txt will be created in C:\Users\Public\
    
  - ✅ Open privilege_test.txt to check the execution context: tnagata-pc\tnagata
    
  - ❌ No privilege escalation confirmed

### 4. Expected Output
✅ calc.exe launches → Confirms code execution

✅ privilege_test.txt contains the execution context

Example: tnagata-pc\tnagata

➡️ If the output shows nt authority/system → Privilege escalation confirmed

➡️ If the output shows current user (tnagata) → Code execution confirmed

🔥 Impact
 - Code Execution: ✅ Confirmed
 - Privilege Escalation: ❌ Not confirmed

📝 Suggested Fix
 - ✔️ Use Safe DLL Search Mode to prevent loading from the working directory.
 - ✔️ Sign and validate all loaded DLLs.
 - ✔️ Load DLLs using absolute paths instead of relying on search order.

👤 Discoverer(s)
 - Toshiro Nagata Bolivar (Open-Sec)

🎥 PoC Video
 -  https://youtu.be/y75aEasRxOo

✅ Status

 - 🟢 CVE Report Submitted
   
 - 🟢 Awaiting Confirmation from MITRE
