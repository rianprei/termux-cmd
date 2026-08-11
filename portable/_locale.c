#include "cmd.h"

LCID GetUserDefaultLCID(void) {
	return 1;
}

int GetLocaleInfo(
  LCID   Locale,
  LCTYPE LCType,
  LPTSTR lpLCData,
  int    cchData
) {
	switch( LCType ) {
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dd373757(v=vs.85).aspx
	case LOCALE_IDATE:
		strncpy(lpLCData, "1", cchData);
		break;

	// https://msdn.microsoft.com/en-us/library/windows/desktop/dd373829(v=vs.85).aspx
	case LOCALE_S2359:
		strncpy(lpLCData, "p", cchData);
		break;

	case LOCALE_S1159:
		strncpy(lpLCData, "a", cchData);
		break;

	case LOCALE_STIME:
		strncpy(lpLCData, ":", cchData);
		break;

	case LOCALE_SDATE:
		strncpy(lpLCData, "/", cchData);
		break;

	case LOCALE_ITIME:
		strncpy(lpLCData, "0", cchData);
		break;

	case LOCALE_ICENTURY:
		strncpy(lpLCData, "1", cchData);
		break;

	case LOCALE_SSHORTDATE:
		strncpy(lpLCData, "dd/MM/yyyy", cchData);
		break;

	case LOCALE_SDECIMAL:
		strncpy(lpLCData, ",", cchData);
		break;

	case LOCALE_STHOUSAND:
		strncpy(lpLCData, ".", cchData);
		break;

	case LOCALE_SABBREVDAYNAME1:
		strncpy(lpLCData, "Sun", cchData);
		break;

	case LOCALE_SABBREVDAYNAME2:
		strncpy(lpLCData, "Mon", cchData);
		break;

	case LOCALE_SABBREVDAYNAME3:
		strncpy(lpLCData, "Tue", cchData);
		break;

	case LOCALE_SABBREVDAYNAME4:
		strncpy(lpLCData, "Wed", cchData);
		break;

	case LOCALE_SABBREVDAYNAME5:
		strncpy(lpLCData, "Thu", cchData);
		break;

	case LOCALE_SABBREVDAYNAME6:
		strncpy(lpLCData, "Fri", cchData);
		break;

	case LOCALE_SABBREVDAYNAME7:
		strncpy(lpLCData, "Sat", cchData);
		break;

	default:
		return 0;
	}

	return 1;
}