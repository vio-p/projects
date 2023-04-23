#include "UserBasedRG.h"

UserBasedRG::UserBasedRG(const DbUser& user)
{
}

DbShow UserBasedRG::GetRecommendation()
{
    return DbShow();
}

std::vector<DbShow> UserBasedRG::GetRecommendations(uint16_t numberOfRecommendations)
{
    return std::vector<DbShow>();
}
