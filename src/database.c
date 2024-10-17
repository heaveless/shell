/*
 *
 * credentials {
 * 		id: String Auto
 * 		owner: String
 *		user: String
 *		token: String
 * }
 *
 *	repositories {
 *		id: String Auto
 *		credential: String (credential.id)
 *		ref: String
 *	}
 *
 * images {
 * 		id: String
 *		repository: String (repository.id)
 *		ref: String
 * }
 *
 * */

int initialize(void);

int create_table(void);
int update_table(void);
int delete_table(void);
