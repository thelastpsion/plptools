#ifndef _bufferstore_h
#define _bufferstore_h

#include <sys/types.h>

class ostream;

/**
 * A generic container for an array of bytes.
 *
 * bufferStore provides an array of bytes which
 * can be accessed using various types.
 */
class bufferStore {
public:
	/**
	 * Constructs a new bufferStore.
	 */
	bufferStore();

	/**
	 * Constructs a new bufferStore and
	 * initializes its content.
	 *
	 * @param buf Pointer to data for initialization.
	 * @param len Length of data for initialization.
	 */
	bufferStore(const unsigned char *, long);

	/**
	 * Destroys a bufferStore instance.
	 */
	~bufferStore();

	/**
	 * Constructs a new bufferStore and
	 * initializes its content.
	 *
	 * @param b A bufferStore, whose content is
	 * used for initialization.
	 */
	bufferStore(const bufferStore &);

	/**
	 * Copies a bufferStore.
	 */
	bufferStore &operator =(const bufferStore &);

	/**
	 * Retrieves the length of a bufferStore.
	 *
	 * @returns The current length of the contents
	 * 	in bytes.
	 */
	unsigned long getLen() const;

	/**
	 * Retrieves the byte at index <em>pos</em>.
	 *
	 * @param pos The index of the byte to retrieve.
	 *
	 * @returns The value of the byte at index <em>pos</em>
	 */
	unsigned char getByte(long pos = 0) const;

	/**
	 * Retrieves the word at index <em>pos</em>.
	 *
	 * @param pos The index of the word to retrieve.
	 *
	 * @returns The value of the word at index <em>pos</em>
	 */
	u_int16_t getWord(long pos = 0) const;

	/**
	 * Retrieves the dword at index <em>pos</em>.
	 *
	 * @param pos The index of the dword to retrieve.
	 *
	 * @returns The value of the dword at index <em>pos</em>
	 */
	u_int32_t getDWord(long pos = 0) const;

	/**
	 * Retrieves the characters at index <em>pos</em>.
	 *
	 * @param pos The index of the characters to retrieve.
	 *
	 * @returns A pointer to characters at index <em>pos</em>
	 */
	const char * getString(long pos = 0) const;

	/**
	 * Removes bytes from the start of the buffer.
	 *
	 * @param len Number of bytes to remove.
	 */
	void discardFirstBytes(int len = 0);

	/**
	 * Prints a dump of the content.
	 *
	 * Mainly used for debugging purposes.
	 *
	 * @param s The stream to write to.
	 * @param b The bufferStore do be dumped.
	 *
	 * @returns The stream.
	 */
	friend ostream &operator<<(ostream &, const bufferStore &);

	/**
	 * Tests if the bufferStore is empty.
	 *
	 * @returns true, if the bufferStore is empty.
	 * 	false, if it contains data.
	 */
	bool empty() const;

	/**
	 * Initializes the bufferStore.
	 *
	 * All data is removed, the length is
	 * reset to 0.
	 */
	void init();

	/**
	 * Initializes the bufferStore with
	 * a given data.
	 *
	 * @param buf Pointer to data to initialize from.
	 * @param len Length of data.
	 */
	void init(const unsigned char * buf, long len);

	/**
	 * Appends a byte to the content of this instance.
	 *
	 * @param c The byte to append.
	 */
	void addByte(unsigned char c);

	/**
	 * Appends a word to the content of this instance.
	 *
	 * @param w The word to append.
	 */
	void addWord(int);

	/**
	 * Appends a dword to the content of this instance.
	 *
	 * @param dw The dword to append.
	 */
	void addDWord(long dw);

	/**
	 * Appends a string to the content of this instance.
	 *
	 * The trailing zero byte is <em>not</em> copied
	 * to the content.
	 *
	 * @param s The string to append.
	 */
	void addString(const char *s);

	/**
	 * Appends a string to the content of this instance.
	 *
	 * The trailing zero byte <em>is</em> copied
	 * to the content.
	 *
	 * @param s The string to append.
	 */
	void addStringT(const char *s);

	/**
	 * Appends data to the content of this instance.
	 *
	 * @param buf The data to append.
	 * @param len Length of data.
	 */
	void addBytes(const unsigned char *buf, int len);

	/**
	 * Appends data to the content of this instance.
	 *
	 * @param b The bufferStore whose content to append.
	 * @param maxLen Length of content.
	 */
	void addBuff(const bufferStore &b, long maxLen = -1);
  
	/**
	 * Truncates the buffer.
	 * If the buffer is smaller, does nothing.
	 *
	 * @param newLen The new length of the buffer.
	 */
	void truncate(long newLen);
  
private:
	void checkAllocd(long newLen);

	long len;
	long lenAllocd;
	long start;
	unsigned char * buff;

	enum c { MIN_LEN = 300 };
};

inline bool bufferStore::empty() const {
	return (len - start) == 0;
}

#endif
