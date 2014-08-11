#include <SQLiteInterface.h>
#include <ProcessedPacket.h>
#include <ProcessedHTTPReq.h>
#include <cstring>

SQLiteInterface::SQLiteInterface()
    : db_file("./web_service/db.sqlite3"), insert_history("INSERT INTO History (date, client, host, value) VALUES (?,?,?,?)")
{
//    db_file = "./web_service/db.sqlite3";
//    insert_history = "INSERT INTO History (date, client, host, value) VALUES (?,?,?,?)";
}

bool SQLiteInterface::OpenDatabase()
{
    int result = sqlite3_open(this->db_file, &this->db);
	if (result != SQLITE_OK)
	{
		cout << "Failed to open database " << sqlite3_errstr(result) << endl;
		sqlite3_close(db);
		return false;
	}

	debug_print("Opened database %s" << this->db_file);
	return true;
}

bool SQLiteInterface::InsertHistory(ProcessedPacket *info)
{
    int result;
    sqlite3_stmt *stmt;

    /* prepare the insert sql, leave stmt ready for loop */
	result = sqlite3_prepare_v2(this->db, this->insert_history, strlen(this->insert_history) + 1, &stmt, 0);
	if (result != SQLITE_OK) {
		debug_print("Failed to prepare database " << sqlite3_errstr(result));
		//sqlite3_close(this->db);
		return false;
	}

	debug_print("SQL prepared OK");
	/* bind parameters */
	sqlite3_bind_int64(stmt, 1, (time_t) info->time);

	const char *client = info->client.mac_name.c_str();
	sqlite3_bind_text(stmt, 2, client, strlen(client), SQLITE_STATIC);

	const char *host = info->host.c_str();
    sqlite3_bind_text(stmt, 3, host, strlen(host), SQLITE_STATIC);

    sqlite3_bind_int(stmt, 4, info->no_pkt);

    result = sqlite3_step(stmt);
    return true;
}

bool SQLiteInterface::InsertHTTPReq(ProcessedHTTPReq *info)
{
    return false;
}

bool SQLiteInterface::CloseDatabase()
{
    sqlite3_close(this->db);
    return true;
}
