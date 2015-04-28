/* File Name: file_op.h
 *
 * Description:
 *
 * Created by henuyx on 2015-04-28
 *
 */

#ifndef __FILE_OP_H__
#define __FILE_OP_H__

/*******************INCLUDE*******************************/
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <errno.h>

/*******************GLOBAL********************************/

class FileOp
{
public:
	FileOp(void);
	~FileOp(void);

	/* open file, return 0 for success, -1 for failed */
	int open_file(const char *filename, int flags, mode_t mode);
	/* close file, return 0 for success, -1 for failed */
	int close_file();

	/* read n bytes by position offset, save data into ptr
	 * return bytes have read, -1 for failed
	 */
	ssize_t read_offset_n(char *ptr, off_t offset, size_t n);
	/* read n bytes by current offset, save data into ptr
	 * return bytes have read, -1 for failed
	 */
	ssize_t read_n(char *ptr, size_t n);
	/* write n bytes by position offset, the data from ptr
	 * return bytes have written, -1 for failed
	 */
	ssize_t write_offset_n(const char *ptr, off_t offset, size_t n);
	/* write n bytes by current offset, the data from ptr
	 * return bytes have written, -1 for failed
	 */
	ssize_t write_n(const char *ptr, size_t n);

	/* seek file position, return current position for success, -1 for failed */
	off_t seek(off_t offset);
	/* trunted file into zero, return 0 for success, -1 for failed */
	int trucate_file_zero();
	/* get file size, return file size for success, -1 for failed */
	off_t get_file_size();
	/* is file opened, return true for opened, false for closed */
	bool is_file_opened();

private:
	/* file descriptor */
	int fd_;
	/* opend flag, true when opended, false when closed */
	bool opened_;
	/* file name */
	std::string file_;
};

#endif

/*******************EOF***********************************/
