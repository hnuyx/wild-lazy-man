/* File Name: mysql_op.cpp
 *
 * Description: mysql operation 
 *
 * Created by henuyx on 2015-04-29
 *
 */

/*******************INCLUDE*******************************/
#include "mysql_op.h"

/*******************GLOBAL********************************/

MysqlOp::MysqlOp() : m_result(NULL), m_connected_flag(false)
{
	// clear field data
	clear_field_data();
}

MysqlOp::MysqlOp(const std::string &ip, const BL_NS::uint32 port,
	const std::string &db_name, const std::string &user, const std::string &passwd) : m_result(NULL), m_connected_flag(false)
{
	// clear field data
	clear_field_data();

	// set data
	set_data(ip, port, db_name, user, passwd);
}

MysqlOp::~MysqlOp()
{
	// free result
	free_result();
	// clear field data
	clear_field_data();
	// disconnect
	if(m_connected_flag)
	{
		disconnect_mysql();
	}
}


/* set data */
void MysqlOp::set_data(const std::string &ip, const BL_NS::uint32 port,
	const std::string &db_name, const std::string &user, const std::string &passwd)
{
	m_ip = ip;
	m_port = port;
	m_db_name = db_name;
	m_user = user;
	m_passwd = passwd;
}


/* connect, return 0 for success, -1 for failed */
int MysqlOp::connect_mysql()
{
	// already connected
	if(m_connected_flag)
	{
		fprintf(stderr, "has already been connected [%s:%u]--[%s:%s]\n",
			m_ip.c_str(), m_port, m_db_name.c_str(), m_user.c_str());
		return 0;
	}

	// clear field data
	clear_field_data();

	// set flag
	m_connected_flag = false;

	// init handler
	if(NULL == mysql_init(&m_db_handler))
	{
		fprintf(stderr, "init mysql hanlder failed [%s:%u]--[%s:%s]: %s\n",
			m_ip.c_str(), m_port, m_db_name.c_str(), m_user.c_str(),
			mysql_error(&m_db_handler));
		return -1;
	}

	// connect
	if(NULL == mysql_real_connect(&m_db_handler, m_ip.c_str(),
		m_user.c_str(), m_passwd.c_str(), m_db_name.c_str(), m_port, NULL, 0))
	{
		fprintf(stderr, "connect failed [%s:%u]--[%s:%s]: %s\n",
			m_ip.c_str(), m_port, m_db_name.c_str(), m_user.c_str(),
			mysql_error(&m_db_handler));
		return -1;
	}

	// connect success
	fprintf(stderr, "connect success [%s:%u]--[%s:%s]\n",
		m_ip.c_str(), m_port, m_db_name.c_str(), m_user.c_str());

	m_connected_flag = true;
	return 0;
}

/* connect, return 0 for success, -1 for failed */
int MysqlOp::connect_mysql(const std::string &ip, const BL_NS::uint32 port,
	const std::string &db_name, const std::string &user, const std::string &passwd)
{
	// already connected
	if(m_connected_flag)
	{
		fprintf(stderr, "has already been connected [%s:%u]--[%s:%s]\n",
			m_ip.c_str(), m_port, m_db_name.c_str(), m_user.c_str());
		return 0;
	}

	// set data and connect mysql
	set_data(ip, port, db_name, user, passwd);
	return connect_mysql();
}

/* disconnect */
void MysqlOp::disconnect_mysql()
{
	// disconnect
	mysql_close(&m_db_handler);

	// set flag
	m_connected_flag = false;
}


/* execute commend, return 0 for success, -1 for failed */
int MysqlOp::execute_mysql(const char *sql_str)
{
	// wrong sql-string
	if((NULL == sql_str) || (0 == strlen(sql_str)))
	{
		fprintf(stderr, "NULL sql-str or 0 lenght sql-str\n");
		return -1;
	}

	// disconnected
	if(!m_connected_flag)
	{
		fprintf(stderr, "mysql is disconnected\n");
		return -1;
	}

	// free pre-result
	free_result();

	// clear field data
	clear_field_data();

	// execute sql-string
	if(0 != mysql_real_query(&m_db_handler, sql_str, strlen(sql_str)))
	{
		fprintf(stderr, "execute sql-str failed: %s, error: %s\n", sql_str, mysql_error(&m_db_handler));
		return -1;
	}

	return 0;
}

/* reconnect, return 0 for success, -1 for failed */
int MysqlOp::reconnect()
{
	disconnect_mysql();
	return connect_mysql();
}


/* free data */
void MysqlOp::free_result()
{
	// free result
	if(NULL != m_result)
	{
		mysql_free_result(m_result);
		m_result = NULL;
	}
}

/* get field by name */
char* MysqlOp::get_field(const char *field_name)
{
	// init row
	if(0 != init_field_data())
	{
		return NULL;
	}

	// null row
	if(NULL == m_row)
	{
		return NULL;
	}

	// get field index
	int idx = m_field_idx_map[field_name];
	// wrong index
	if(idx >= m_field_num)
	{
		return NULL;
	}

	return m_row[idx];
}

/* get row */
char** MysqlOp::get_row()
{
	// init row
	if(0 != init_field_data())
	{
		return NULL;
	}

	m_row = mysql_fetch_row(m_result);
	return m_row;
}

// clear field data
void MysqlOp::clear_field_data()
{
	m_row = NULL;
	m_field_idx_map.clear();
	m_field_num = 0;
	m_row_flag = false;
}

/* init field data, return 0 for success, -1 for failed */
int MysqlOp::init_field_data()
{
	// has already init field data
	if(m_row_flag)
	{
		return 0;
	}

	// store result
	m_result = mysql_store_result(&m_db_handler);
	if(NULL == m_result)
	{
		fprintf(stderr, "store result error: %s\n", mysql_error(&m_db_handler));
		return -1;
	}

	// fields number
	m_field_num = mysql_num_fields(m_result);

	// fields map
	MYSQL_FIELD *tfields = mysql_fetch_fields(m_result);
	for(int i = 0; i < m_field_num; i ++)
	{
		m_field_idx_map[tfields[i].name] = i;
	}

	m_row_flag = true;
	return 0;
}

/*******************EOF***********************************/
