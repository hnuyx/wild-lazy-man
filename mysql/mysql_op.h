/* File Name: mysql_op.h
 *
 * Description: mysql operation 
 *
 * Created by heuyx on 2015-04-29
 *
 */

#ifndef __MYSQL_OP_H__
#define __MYSQL_OP_H__

/*******************INCLUDE*******************************/
#include <string>
#include <mysql/mysql.h>
#include <map>

#include "bl_common.h"

/*******************GLOBAL********************************/

class MysqlOp
{
public:
	MysqlOp();
	MysqlOp(const std::string &ip, const BL_NS::uint32 port,
		const std::string &db_name, const std::string &user, const std::string &passwd);
	~MysqlOp();

	/* set data */
	void set_data(const std::string &ip, const BL_NS::uint32 port,
		const std::string &db_name, const std::string &user, const std::string &passwd);

	/* connect, return 0 for success, -1 for failed */
	int connect_mysql();
	int connect_mysql(const std::string &ip, const BL_NS::uint32 port,
		const std::string &db_name, const std::string &user, const std::string &passwd);
	/* disconnect */
	void disconnect_mysql();

	/* execute commend, return 0 for success, -1 for failed */
	int execute_mysql(const char *sql_str);

private:
	/* reconnect, return 0 for success, -1 for failed */
	int reconnect();

	/* free result */
	void free_result();

public:
	/* get field by name */
	char* get_field(const char *field_name);
	/* get row */
	char** get_row();
private:
	// clear field data
	void clear_field_data();
	/* init field data, return 0 for success, -1 for failed */
	int init_field_data();
private:
	// mysql row
	MYSQL_ROW m_row;
	// map for fields
	typedef std::map<std::string, int> FieldIndexMap;
	FieldIndexMap m_field_idx_map;
	// fields number
	int m_field_num;
	// row flag, true for has data, false for has no data
	bool m_row_flag;

private:
	// mysql handler
	MYSQL m_db_handler;
	// query result
	MYSQL_RES *m_result;

	// ip, port
	std::string m_ip;
	BL_NS::uint32 m_port;

	// database name, user name, password
	std::string m_db_name;
	std::string m_user;
	std::string m_passwd;

	// connected flag, true for connected, false for disconnected
	bool m_connected_flag;
};

#endif

/*******************EOF***********************************/
