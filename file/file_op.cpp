/* File Name: file_op.cpp
 *
 * Description:
 *
 * Created by henuyx on 2015-04-28
 *
 */

/*******************INCLUDE*******************************/
#include "file_op.h"

/*******************GLOBAL********************************/

FileOp::FileOp(void) : opened_(false)
{
}

FileOp::~FileOp(void)
{
	close_file();
}

/* open file, return 0 for success, -1 for failed */
int FileOp::open_file(const char *filename, int flags, mode_t mode)
{
	close_file();

	this->file_ = filename;
	this->fd_ = open(filename, flags, mode);
	if(this->fd_ < 0)
	{
		this->opened_ = false;
		perror("open file  failed:");
		return -1;
	}
	this->opened_ = true;

	return 0;
}

/* close file, return 0 for success, -1 for failed */
int FileOp::close_file()
{
	if(this->fd_ > 0 && this->opened_)
	{
		this->opened_ = false;
		close(this->fd_);
		return 0;
	}

	return -1;
}

/* read file n bytes by position offset, save data into ptr
 * return bytes have read, -1 for failed
 */
ssize_t FileOp::read_offset_n(char *ptr, off_t offset, size_t n)
{
	if(this->opened_)
	{
		lseek(this->fd_, offset, SEEK_SET);
		return read_n(ptr, n);
	}

	return -1;
}

/* read file n bytes by current offset, save data into ptr
 * return bytes have read, -1 for failed
 */
ssize_t FileOp::read_n(char *ptr, size_t n)
{
	if(this->opened_)
	{
		size_t nleft = n;
		ssize_t nread;
		while(nleft > 0)
		{
			if((nread = read(this->fd_, ptr, nleft)) < 0)
			{
				if(nleft == n)
					return -1;
				else
					break;
			}
			else if(nread == 0)
			{
				break;
			}

			nleft -= nread;
			ptr += nread;
		}
		return (n - nleft);
	}

	return -1;
}

/* write file n bytes by position offset, the data from ptr
 * return bytes have written, -1 for failed
 */
ssize_t FileOp::write_offset_n(const char *ptr, off_t offset, size_t n)
{
	if(this->opened_)
	{
		lseek(this->fd_, offset, SEEK_SET);
		write_n(ptr, n);
	}

	return -1;
}

/* write file n bytes by current offset, the data from ptr
 * return bytes have written, -1 for failed
 */
ssize_t FileOp::write_n(const char *ptr, size_t n)
{
	if(this->opened_)
	{
		size_t nleft = n;
		ssize_t nwrite;
		while(nleft > 0)
		{
			if((nwrite = write(this->fd_, ptr, nleft)) < 0)
			{
				return -1;
			}
			else if(nwrite==0)
			{
				break;
			}

			nleft -= nwrite;
			ptr += nwrite;
		}
		return (n - nleft);
	}

	return -1;
}

/* seek file position, return current position for success, -1 for failed */
off_t FileOp::seek(off_t offset)
{
	return lseek(this->fd_, offset, SEEK_SET);
}

/* trunted file into zero, return 0 for success, -1 for failed */
int FileOp::trucate_file_zero()
{
	return ftruncate(this->fd_, 0);
}

/* get file size, return file size for success, -1 for failed */
off_t FileOp::get_file_size()
{
	if(this->opened_)
	{
		return lseek(this->fd_, 0, SEEK_END);
	}
	return -1;
}

/* is file opened, return true for opened, false for closed */
bool FileOp::is_file_opened()
{
	return this->opened_;
}

/*******************EOF***********************************/
