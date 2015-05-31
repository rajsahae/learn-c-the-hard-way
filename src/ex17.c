#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static const int MAX_DATA = 512;
static const int MAX_ROWS = 100;

/* TODO
 * Change the code to accept parameters for MAX_DATA and MAX_ROWS,
 * store them in the Database struct, and write that to the file,
 * thus creating a database that can be arbitrarily sized. (partially done)
 *
 * Add more operations you can do on the database, like find.
 *
 * Add some more fields to the Address and make them searchable.
 *
 * Try reworking the program to use a single global for the
 * database connection. How does this new version of the
 * program compare to the other one?
 *
 * Go research "stack data structure" and write one in 
 * your favorite language, then try to do it in C.
 */

/*
 * Address struct
 */
struct Address {
  int id;
  int set;
  char* name;
  char* email;
};

struct Address* Address_create(const int max_size)
{
  struct Address* addr = malloc(sizeof(struct Address));
  addr->name           = malloc(max_size);
  addr->email          = malloc(max_size);

  return addr;
}

void Address_destroy(struct Address* addr)
{
  if ( addr ) {
    if ( addr->name ) free(addr->name);
    if ( addr->email ) free(addr->email);

    free(addr);
  }
}

void Address_print(struct Address* addr)
{
  printf("%3d: %s <%s>\n", addr->id, addr->name, addr->email);
}

/*
 * Database struct
 */
struct Database {
  struct Address rows[MAX_ROWS];
};

/*
 * Connection struct
 */
struct Connection {
  FILE* file;
  struct Database* db;
};

void Database_close(struct Connection*);

void die(const char* message, struct Connection* conn)
{
  if(errno) {
    perror(message);
  }
  else {
    printf("ERROR: %s\n", message);
  }

  if ( conn ) {
    Database_close(conn);
  }

  exit(1);
}

void Database_load(struct Connection* conn)
{
  int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if ( rc != 1 ) {
    die("Failed to load database", conn);
  }

  int i = 0;
  for ( i = 0 ; i < MAX_ROWS ; i++ ) {
    conn->db->rows[i] = *Address_create(MAX_DATA);
    fread(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    fread(&conn->db->rows[i].set, sizeof(int), 1, conn->file);

    if (conn->db->rows[i].set) {
      fread(conn->db->rows[i].name, MAX_DATA, 1, conn->file);
      fread(conn->db->rows[i].email, MAX_DATA, 1, conn->file);
    }
  }
}

struct Connection* Database_open(const char* filename, char mode)
{
  struct Connection* conn = malloc(sizeof(struct Connection));
  if ( !conn ) die ("Memory error", conn);

  conn->db = malloc(sizeof(struct Database));
  if ( !conn->db ) die("Memory error", conn);

  if ( mode == 'c' ) {
    conn->file = fopen(filename, "w");
  }
  else {
    conn->file = fopen(filename, "r+");

    if ( conn->file ) {
      Database_load(conn);
    }
  }

  if ( !conn->file ) die("Failed to open the file", conn);

  return conn;
}

void Database_close(struct Connection* conn)
{
  if ( conn ) {
    if ( conn->file ) fclose(conn->file);
    if ( conn->db   ) {

      int i = 0;
      for ( i = 0 ; i < MAX_ROWS ; i++ ) {
        // printf("Destroying address: %d\n", i);
        // Address_destroy(&conn->db->rows[i]);
      }

      free(conn->db);
    }
    free(conn);
  }
}

void Database_write(struct Connection* conn)
{
  rewind(conn->file);

  int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if ( rc != 1 ) die("Failed to write database", conn);

  int i = 0;
  for ( i = 0 ; i < MAX_ROWS ; i++ ) {
    fwrite(&conn->db->rows[i].id, sizeof(int), 1, conn->file);
    fwrite(&conn->db->rows[i].set, sizeof(int), 1, conn->file);

    if (conn->db->rows[i].set) {
      fwrite(conn->db->rows[i].name, MAX_DATA, 1, conn->file);
      fwrite(conn->db->rows[i].email, MAX_DATA, 1, conn->file);
    }
  }

  rc = fflush(conn->file);
  if ( rc == -1 ) die("Cannot flush database", conn);
}

void Database_create(struct Connection* conn)
{
  int i = 0;

  for ( i = 0 ; i < MAX_ROWS ; i++ ) {
    conn->db->rows[i] = *Address_create(MAX_DATA);
    conn->db->rows[i].id  = i;
    conn->db->rows[i].set = 0;
  }
}

void Database_set(struct Connection* conn, int id, const char* name, const char* email)
{
  struct Address* addr = &conn->db->rows[id];
  if ( addr->set ) die("Already set, delete it first", conn);

  // printf("strlen name: %lu\n", strlen(name) );
  // printf("strlen email: %lu\n", strlen(email) );

  addr->set = 1;
  // WARNING: bug, read the "How To Break It" and fix this
  char* res = strncpy(addr->name, name, MAX_DATA);
  // demonstrate the strncpy bug
  if ( !res ) die("Email copy failed", conn);

  // fix the strncpy bug by adding the terminator if needed
  if ( strlen(name) >= MAX_DATA ) {
    // puts("name was too long, adding terminator");
    addr->name[MAX_DATA-1] = '\0';
  }

  res = strncpy(addr->email, email, MAX_DATA);
  if ( !res ) die("Email copy failed", conn);

  // fix the strncpy bug by adding the terminator if needed
  if ( strlen(email) >= MAX_DATA ) {
    // puts("email was too long, adding terminator");
    addr->email[MAX_DATA-1] = '\0';
  }
}

void Database_get(struct Connection* conn, int id)
{
  struct Address* addr = &conn->db->rows[id];

  if ( addr->set ) {
    Address_print(addr);
  }
  else {
    die("ID is not set", conn);
  }
}

void Database_delete(struct Connection* conn, int id)
{
  struct Address addr = {.id = id, .set = 0};
  conn->db->rows[id] = addr;
}

void Database_list(struct Connection* conn)
{
  int i = 0;
  struct Database* db = conn->db;

  for ( i = 0 ; i < MAX_ROWS ; i++ ) {
    struct Address* cur = &db->rows[i];

    if ( cur->set ) {
      Address_print(cur);
    }
  }
}

int main(int argc, char* argv[])
{
  if ( argc < 3 ) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

  char* filename = argv[1];
  char action = argv[2][0];
  struct Connection* conn = Database_open(filename, action);
  int id = 0;

  if ( argc > 3 ) id = atoi(argv[3]);
  if ( id >= MAX_ROWS) die("There are not that many records", conn);

  switch(action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 'g':
      if ( argc != 4 ) die("Need an id to get", conn);

      Database_get(conn, id);
      break;

    case 's':
      if ( argc != 6 ) die("Need id, name, email to set", conn);

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if ( argc != 4 ) die("Need id to delete", conn);

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
  }

  Database_close(conn);

  return 0;

}
