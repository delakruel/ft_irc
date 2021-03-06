#include "Channel.hpp"

Channel::~Channel() {}

Channel::Channel(std::string name, User &user, std::string password) 
: _password(password), _channelName(name) {
	_inviteOnly = false;
	_hasPassword = (password == "") ? false : true;
	_secret = false;
	_private = false;
	_noOutside = true;
	_moderated = false;
	_topicByOper = true;
	_userLimit = 21;
	_users.push_back(user);
	_operators.push_back(user);
	user.getJoinedChannels().push_back(*this);
}

Channel::Channel(const Channel &copy)
:	_inviteOnly(copy._inviteOnly), _hasPassword(copy._hasPassword),
	_secret(copy._secret), _private(copy._private), _noOutside(copy._noOutside),
	_moderated(copy._moderated), _topicByOper(copy._topicByOper),
	_userLimit(copy._userLimit), _topic(copy._topic), _password(copy._password),
	_channelName(copy._channelName), _users(copy._users), _operators(copy._operators),
	_invites(copy._invites), _voices(copy._voices), _banList(copy._banList) {}

Channel &Channel::operator=(const Channel &copy) {
	if (this == &copy)
		return *this;
	_inviteOnly = copy._inviteOnly;
	_hasPassword = copy._hasPassword;
	_secret = copy._secret;
	_private = copy._private;
	_noOutside = copy._noOutside;
	_moderated = copy._moderated;
	_topicByOper = copy._topicByOper;
	_userLimit = copy._userLimit;
	_topic = copy._topic;
	_password = copy._password;
	_channelName = copy._channelName;
	_users = copy._users;
	_operators = copy._operators;
	_invites = copy._invites;
	_voices = copy._voices;
	_banList = copy._banList;
	return *this;
}

bool Channel::operator==(const Channel &op) const { return _channelName == op.getChannelName(); }

////////////////////////////////
//----------Setters-----------//
////////////////////////////////
void Channel::setPrivateFlag(bool flag) { _private = flag; }
void Channel::setSecretFlag(bool flag) { _secret = flag; }
void Channel::setInviteFlag(bool flag) { _inviteOnly = flag; }
void Channel::setTopicFlag(bool flag) { _topicByOper = flag; }
void Channel::setOutsideFlag(bool flag) { _noOutside = flag; }
void Channel::setModeratedFlag(bool flag) { _moderated = flag; }
void Channel::setUserLimit(unsigned int limit) { _userLimit = limit; }
void Channel::setPassword(std::string pass) { _password = pass; _hasPassword = true; }
void Channel::setTopic(std::string topic) { _topic = topic; }
void Channel::resetPassword() { _password = ""; _hasPassword = false; }

////////////////////////////////
//----------Getters-----------//
////////////////////////////////
bool Channel::inChannel(User user) const{
	for (const_iter it = _users.begin(); it != _users.end(); ++it)
		if (*it == user)
			return true;
	return false;
}
bool Channel::isOperator(User &user) const {
	for (const_iter it = _operators.begin(); it != _operators.end(); ++it)
		if (*it == user)
			return true;
	return false;
}
bool Channel::isUserInvited(User &user) const {
	for (const_iter it = _invites.begin(); it != _invites.end(); ++it)
		if (*it == user)
			return true;
	return false;
}
bool Channel::isInviteOnly() const { return _inviteOnly; }
bool Channel::isPassword() const { return _hasPassword; }
bool Channel::isTopicByOper() const { return _topicByOper; }
bool Channel::isSecret() const { return _secret; }
bool Channel::isPrivate() const { return _private; }
bool Channel::isNotOutside() const { return _noOutside; }
bool Channel::isModerated() const { return _moderated; }
std::string Channel::getChannelName() const { return _channelName; }
std::string Channel::getChannelTopic() const { return _topic; }
std::vector<User>& Channel::getOpers() { return _operators; }
std::vector<User> &Channel::getBanList() { return _banList; }
std::vector<User> &Channel::getVoices() { return _voices; }
std::vector<User> &Channel::getUsers() { return _users; }
std::vector<User> &Channel::getInvites() { return _invites; }

////////////////////////////////
//----------Functions---------//
////////////////////////////////
bool Channel::addUser(User &user, std::string password = "") {
	if (isPassword() && password != _password)
		return false;
	_users.push_back(user);
	return true;
}

void Channel::addUserToBanList(User &user) {
	if (Utils::isUserExist(_banList, user.getNickName()) == false)
		_banList.push_back(user);
}
void Channel::addUserToInviteList(User &user) {
	if (Utils::isUserExist(_invites, user.getNickName()) == false)
		_invites.push_back(user);
}
void Channel::addUserToVoiceList(User &user) {
	if (Utils::isUserExist(_voices, user.getNickName()) == false)
		_voices.push_back(user);
}
void Channel::addOperator(User &user) {
	if (Utils::isUserExist(_operators, user.getNickName()) == false)
		_operators.push_back(user);
}

void Channel::deleteOperator(User &user) {
	iter it = Utils::findUser(_operators, user.getNickName());
	if (it != _operators.end())
		_operators.erase(it);
}
void Channel::deleteUser(User &user) {
	iter it = Utils::findUser(_users, user.getNickName());
	if (it != _users.end())
		_users.erase(it);
}

void Channel::sendToAll(User &sender, std::string channelName, std::string msg) {
	std::string prefix = ":" + sender.getNickName() + "!"
			+ sender.getUserName() + "@" + sender.getRealHost() + " MODE " + channelName + " ";
	for (iter it = _users.begin(); it != _users.end(); ++it)
		Server::sendSocket(it->getSocketFd(), prefix + msg + "\n");
}

bool Channel::isChannelName(std::string chName) {
	if (chName.front() == '#' || chName.front() == '&')
		return true;
	return false;
}

bool Channel::isValidChannelName(std::string chName) {
	if (chName == "")
		return false;
	if (Channel::isChannelName(chName) == false)
		return false;
	for (size_t i = 1; i < chName.length(); i++)
		if ((chName[i] < 'a' || chName[i] > 'z') && (chName[i] < 'A' || chName[i] > 'Z') && (chName[i] < '0' || chName[i] > '9') && chName[i] != '_')
			return false;
	return true;
}
