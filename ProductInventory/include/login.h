#ifndef LOGIN_H
#define LOGIN_H

typedef enum UserRole {
    ROLE_NONE = 0,
    ROLE_ADMIN,
    ROLE_USER
} UserRole;

UserRole login_menu(void);
int admin_login(void);
int user_login(void);

#endif
