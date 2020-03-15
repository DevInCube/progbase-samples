#pragma once

#include <vector>
#include <string>

#include "optional.h"
#include "composer.h"
#include "csv.h"

using std::string;
using std::vector;

class Storage
{
   const string dir_name_;

   vector<Composer> composers_;

   static Composer rowToComposer(const CsvRow &row);
   static CsvRow composerToRow(const Composer &st);

   int getNewComposerId();

 public:
   Storage(const string & dir_name) : dir_name_(dir_name) { }

   bool load();
   bool save();
   // composers
   vector<Composer> getAllComposers(void);
   optional<Composer> getComposerById(int composer_id);
   bool updateComposer(const Composer &composer);
   bool removeComposer(int composer_id);
   int insertComposer(const Composer &composer);
};
 