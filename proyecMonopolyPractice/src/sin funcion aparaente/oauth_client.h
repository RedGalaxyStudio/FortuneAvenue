// oauth_client.h
#ifndef OAUTH_CLIENT_H
#define OAUTH_CLIENT_H

#include <string>

std::string getAuthorizationURL();
void getAccessToken(const std::string& code);

#endif // OAUTH_CLIENT_H
