#ifndef MINE_TOOLS
#define MINE_TOOLS

constexpr LL nulltime = LLONG_MIN;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool Isout;
void getstr(string &s) {
	s.clear();
	char in = getchar();
	while(in == ' ' || in == '\t' || in == '\n' || in == '\r') in = getchar();
	while(in != ' ' && in != '\n' && in != '\r' && in != EOF) s += in, in = getchar();
	if(in == EOF) exit(-1);
}
void getlstr(string &s) {
	s.clear();
	char in = getchar(); 
	while(in != '\n' && in != '\r' && in != EOF) s += in, in = getchar();
	if(in == EOF) exit(-1);
}
LL get() {
    string s;
    bool iserror = 0, islong;
    LL ans, ign;
    do {
	    if(iserror) put("无效数字。\n请输入有效数字: ");
    	iserror = 0, islong = 0, ans = 0;
    	getstr(s);
    	if(s == "/hub") {
    		Isout = 1;
    		return 0;
		}
	    bool have = 0;
	    for(LL i : s) if(i == 'e' || i == 'u' || i == 'E' || i == 'U') {
	    	have = true;
	    	break;
		}
	    if(!sscanf(s.c_str(), "%lld", &ign) || have || (*s.begin() == '0' && s.size() > 1)) {
	    	iserror = 1;
	    	continue;
		}
	    if(s.size() > to_string(LONG_LONG_MAX).size()) {
	    	islong = 1;
	    put("数字过大。\n请输入更小的数字: ");
	    	continue;
		}
		sscanf(s.c_str(), "%lld", &ans);
	} while(iserror || islong);
    return ans;
}
double getf() {
    string s;
    bool iserror = 0, islong;
    double ans, ign;
    do {
	    if(iserror) put("无效数字。\n请输入有效数字: ");
    	iserror = 0, islong = 0, ans = 0;
    	getstr(s);
    	if(s == "/hub") {
    		Isout = 1;
    		return 0;
		}
	    bool have = 0;
	    for(LL i : s) if(i == 'e' || i == 'u' || i == 'E' || i == 'U') {
	    	have = true;
	    	break;
		}
	    if(!sscanf(s.c_str(), "%lf", &ign) || have || (*s.begin() == '0' && s.size() > 1)) {
	    	iserror = 1;
	    	continue;
		}
	    if(s.size() > to_string(LONG_LONG_MAX).size()) {
	    	islong = 1;
	    put("数字过大。\n请输入更小的数字: ");
	    	continue;
		}
		sscanf(s.c_str(), "%lf", &ans);
	} while(iserror || islong);
    return ans;
}
LL randomSeed = -1; 
static std::mt19937 rng = std::mt19937(time(0));
void setRandomSeed(LL seed) { rng.seed(randomSeed = seed); }
void setRandomSeed() { randomSeed = -1, rng.seed(time(0)); }
LL random(LL min, LL max) { return std::uniform_int_distribution <LL> (min, max)(rng); }
string colours[] = { "", "blue", "red", "green", "Lblue", "purple", "yellow", "gray", "cyan", "brown" };
namespace PGB {
	bool eye_protection = 0;
	bool quick_output = 0;
	bool update_check = 1;
}

inline void load_update_check_setting() {
	ifstream fin("PGBUpdateCheck.cfg");
	int enabled = 1;
	if(fin >> enabled) PGB::update_check = enabled != 0;
}

inline void save_update_check_setting() {
	ofstream fout("PGBUpdateCheck.cfg");
	if(fout) fout << (PGB::update_check ? 1 : 0);
}

inline bool check_for_updates() {
	if(!PGB::update_check) return false;
	char tempPath[MAX_PATH];
	char exePath[MAX_PATH];
	if(!GetTempPathA(MAX_PATH, tempPath) || !GetModuleFileNameA(nullptr, exePath, MAX_PATH)) return false;
	string base = string(tempPath) + "PGBUpdateCheck_" + to_string(GetCurrentProcessId());
	string scriptPath = base + ".bat";
	string resultPath = base + ".result";
	const char* script = R"BAT(@echo off
setlocal
set "exe=%~1"
set "result=%~2"
set "json=%TEMP%\PGBUpdateCheck_%RANDOM%.json"
set "remote="
curl.exe -fsSL -A "PlainGameBox" "https://api.github.com/repos/ganyvze/pgb/releases/latest" -o "%json%" >nul 2>nul
if errorlevel 1 goto unavailable
set "PGB_JSON=%json%"
for %%A in ("%exe%") do set "PGB_ASSET=%%~nxA"
set "PGB_EXE=%exe%"
for /f "delims=" %%A in ('powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "$j=Get-Content -Raw -LiteralPath $env:PGB_JSON ^| ConvertFrom-Json; $a=@($j.assets ^| Where-Object { $_.name -eq $env:PGB_ASSET })[0]; if(-not $a){$a=@($j.assets ^| Where-Object { $_.name -match '\.exe$' })[0]}; if($a -and $a.digest){$a.digest -replace '^^sha256:',''} elseif($a){$p=Join-Path $env:TEMP ('PGBUpdateAsset_' + [guid]::NewGuid() + '.bin'); try { Invoke-WebRequest -UseBasicParsing -Uri $a.browser_download_url -OutFile $p; (Get-FileHash -Algorithm SHA256 -LiteralPath $p).Hash } finally { Remove-Item $p -Force -ErrorAction SilentlyContinue }}"') do set "remote=%%A"
if not defined remote goto unavailable
for /f "delims=" %%A in ('powershell.exe -NoProfile -Command "(Get-FileHash -Algorithm SHA256 -LiteralPath $env:PGB_EXE).Hash"') do set "local=%%A"
if /i "%local%"=="%remote%" >"%result%" echo OK
if /i not "%local%"=="%remote%" >"%result%" echo UPDATE
goto cleanup
:unavailable
>"%result%" echo UNAVAILABLE
:cleanup
del "%json%" >nul 2>nul
)BAT";
	{ ofstream fout(scriptPath, ios::binary); if(!fout) return false; fout << script; }
	string command = "cmd.exe /d /c call \"" + scriptPath + "\" \"" + exePath + "\" \"" + resultPath + "\"";
	vector<char> commandBuffer(command.begin(), command.end());
	commandBuffer.push_back('\0');
	STARTUPINFOA startupInfo{};
	startupInfo.cb = sizeof(startupInfo);
	PROCESS_INFORMATION processInfo{};
	bool launched = CreateProcessA(nullptr, commandBuffer.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInfo);
	if(!launched) { DeleteFileA(scriptPath.c_str()); return false; }
	DWORD status = WaitForSingleObject(processInfo.hProcess, 15000);
	if(status == WAIT_TIMEOUT) TerminateProcess(processInfo.hProcess, 1);
	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
	ifstream result(resultPath);
	string state;
	result >> state;
	DeleteFileA(scriptPath.c_str());
	DeleteFileA(resultPath.c_str());
	return state == "UPDATE";
}
inline bool install_update() {
	char tempPath[MAX_PATH];
	char exePath[MAX_PATH];
	if(!GetTempPathA(MAX_PATH, tempPath) || !GetModuleFileNameA(nullptr, exePath, MAX_PATH)) return false;
	string base = string(tempPath) + "PGBUpdateInstall_" + to_string(GetCurrentProcessId());
	string scriptPath = base + ".bat";
	const char* script = R"BAT(@echo off
setlocal
set "exe=%~1"
set "pid=%~2"
set "json=%TEMP%\PGBUpdateInstall_%RANDOM%.json"
set "download=%TEMP%\PGBUpdateInstall_%RANDOM%.exe"
set "updated=0"
curl.exe -fsSL -A "PlainGameBox" "https://api.github.com/repos/ganyvze/pgb/releases/latest" -o "%json%" >nul 2>nul
if errorlevel 1 goto cleanup
set "PGB_JSON=%json%"
set "PGB_DOWNLOAD=%download%"
set "PGB_EXE=%exe%"
for /f "delims=" %%A in ('powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "$j=Get-Content -Raw -LiteralPath $env:PGB_JSON ^| ConvertFrom-Json; $a=@($j.assets ^| Where-Object { $_.name -eq ([IO.Path]::GetFileName($env:PGB_EXE)) })[0]; if(-not $a){$a=@($j.assets ^| Where-Object { $_.name -match '\.exe$' })[0]}; if($a){$a.browser_download_url}"') do set "url=%%A"
if not defined url goto cleanup
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Invoke-WebRequest -UseBasicParsing -Uri '%url%' -OutFile $env:PGB_DOWNLOAD" >nul 2>nul
if not exist "%download%" goto cleanup
:wait
tasklist /FI "PID eq %pid%" | find "%pid%" >nul
if not errorlevel 1 (timeout /t 1 /nobreak >nul & goto wait)
move /Y "%download%" "%exe%" >nul
if errorlevel 1 goto cleanup
set "updated=1"
start "" "%exe%"
:cleanup
if "%updated%"=="0" start "" "%exe%"
del "%json%" >nul 2>nul
del "%download%" >nul 2>nul
del "%~f0" >nul 2>nul
)BAT";
	{ ofstream fout(scriptPath, ios::binary); if(!fout) return false; fout << script; }
	string command = "cmd.exe /d /c call \"" + scriptPath + "\" \"" + exePath + "\" \"" + to_string(GetCurrentProcessId()) + "\"";
	vector<char> commandBuffer(command.begin(), command.end());
	commandBuffer.push_back('\0');
	STARTUPINFOA startupInfo{};
	startupInfo.cb = sizeof(startupInfo);
	PROCESS_INFORMATION processInfo{};
	bool launched = CreateProcessA(nullptr, commandBuffer.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW | DETACHED_PROCESS, nullptr, nullptr, &startupInfo, &processInfo);
	if(!launched) { DeleteFileA(scriptPath.c_str()); return false; }
	CloseHandle(processInfo.hThread);
	CloseHandle(processInfo.hProcess);
	return true;
}
void chco(string s) {
	if(PGB::eye_protection) return ;
    if(s == colours[1]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    else if(s == colours[2]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    else if(s == colours[3]) SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    else if(s == colours[4]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
    else if(s == colours[5]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
    else if(s == colours[6]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else if(s == colours[7]) SetConsoleTextAttribute(hConsole, 0x08);
    else if(s == colours[8]) SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if(s == colours[9]) SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    else SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
    return ;
}
void chco(LL colourid) { chco(colours[colourid]); }
void pause()
{ getch(); }

#endif
