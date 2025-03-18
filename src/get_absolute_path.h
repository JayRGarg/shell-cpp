#ifndef GET_ABSOLUTE_PATH_H
#define GET_ABSOLUTE_PATH_H

#include <filesystem>
#include <string>

std::filesystem::path get_absolute_path(const std::filesystem::path& working_dir, const std::string& relative_path);

#endif // GET_ABSOLUTE_PATH_H 