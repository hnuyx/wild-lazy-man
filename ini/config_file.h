/* File Name: config_file.h
 *
 * Description: config file: open, read, write, save, close
 *
 * Created by liuheng on 2015-05-13
 *
 */

#ifndef __CONFIG_FILE_H__
#define __CONFIG_FILE_H__

/*******************INCLUDE*******************************/

/*******************GLOBAL********************************/

//  max string size
#define MAX_NAME_VALUE_SIZE	64

// return value
#define CONFIG_SUCCESS	0
#define CONFIG_FAILED	-1

// config item, name and vlue, singly-linked list
typedef struct _CONFIG_ITEM
{
	char *name;
	char *value;
	struct _CONFIG_ITEM *next;
} ConfigItem;

// cpp environment
#ifdef __cplusplus
extern "C"
{
#endif

/* Function Name: open_config
 *
 * Description: open config file and get file descriptor
 *
 * Param:
 * fullname: full path name of configuration
 * handle: FILE descriptor
 *
 * Return: return CONFIG_SUCCESS for success, or CONFIG_FAILED for failed
 */
int open_config(const char *fullname, void **handle);

/* Function Name: close_config
 *
 * Description: close config file, and release all resource
 *
 * Param:
 * handle: FILE descriptor
 *
 * Return: return CONFIG_SUCCESS for success, or CONFIG_FAILED for failed
 */
int close_config(void *handle);

/* Function Name: read_value
 *
 * Description: read value by handle and name
 *
 * Param:
 * handle: FILE descriptor
 * name: config name
 * value: the value of name, in for default, out for ret, in-out param.
 *
 * Return: return CONFIG_SUCCESS for success, or CONFIG_FAILED for failed, the ret is stored in value
 */
int read_value(void *handle, const char *name, char *value);

/* Function Name: update_value
 *
 * Description: update value by handle and name,
 *		if name is not exist, and both name and value are not NULL, then add a new paire of name-value
 *		if name is exist and value is NULL then delete the node of the name
 *
 * Param:
 * handle: FILE descriptor
 * name: config name
 * value: the value of name
 *
 * Return: return CONFIG_SUCCESS for success, or CONFIG_FAILED for failed
 */
int update_value(void *handle, const char *name, const char *value);


#ifdef __cplusplus
}
#endif

#endif

/*******************EOF***********************************/
