//
//  idiomAnalyzer.cpp
//  CriptBreaker
//
//  Created by Rodrigo Bueno Tomiosso on 20/08/15.
//  Copyright (c) 2015 mourodrigo. All rights reserved.
//

#include "CripTools.h"

class idiom {
    vector<ui> caracteres_allowed;
    vector<string> s_caracteres_allowed;
    vector<string> idioms;
public:
    idiom (vector<string> _caracteres_allowed,vector<string> _idioms){
        string s = _caracteres_allowed.at(0);
        for (int x ; x<_caracteres_allowed.size(); x++) {
            caracteres_allowed.push_back((unsigned int)stoul (_caracteres_allowed.at(x),nullptr,0));
            s_caracteres_allowed.push_back(_caracteres_allowed.at(x));
        }
        idioms = _idioms;
    }
};

vector<idiom> initIdioms(){
    vector<idiom> idioms;
    
    idioms.push_back(idiom({"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"},{"English","Hawaiian","Indonesian","Latin","Malay","Swahili","Zulu"}));
    idioms.push_back(idiom({"à","é","ë","ï",""},{"Dutch"}));
    idioms.push_back(idiom({"ê","é","ë"},{"Afrikaans"}));
    idioms.push_back(idiom({"ê","ô","ú","û",""},{"WestFrisian"}));
    idioms.push_back(idiom({"Æ","Ø","Å","æ","ø","å"},{"Danish","Norwegian"}));
    idioms.push_back(idiom({"Ä","Ö","ä","ö"},{"Finnish"}));
    idioms.push_back(idiom({"Å","Ä","Ö","å","ä","ö"},{"Swedish"}));
    idioms.push_back(idiom({"Ä","Ö","Õ","Ü","ä","ö","õ","ü"},{"Estonian"}));
    idioms.push_back(idiom({"Ä","Ö","Ü","ä","ö","ü","ß"},{"German"}));
    
    idioms.push_back(idiom({"Ç","Ê","Î","Ş","Û","ç","ê","î","ş","û"},{"Kurdish"}));
    idioms.push_back(idiom({"Ă","Î","Â","Ş","Ţ","ă","î","â","ş","ţ"},{"Romanian"}));
    idioms.push_back(idiom({"Â","Ê","Î","Ô","Û","Ŵ","Ŷ","â","ê","î","ô","û","ŵ","ŷ","á","é","í","ï"},{"Welsh"}));
    idioms.push_back(idiom({"Ĉ","Ĝ","Ĥ","Ĵ","Ŝ","Ŭ","ĉ","ĝ","ĥ","ĵ","ŝ","ŭ"},{"Esperanto"}));
    idioms.push_back(idiom({"Ç","Ğ","İ","Ö","Ş","Ü","ğ","ç","ı","ö","ş","ü"},{"Turkish"}));
    idioms.push_back(idiom({"Á","Ð","É","Í","Ó","Ú","Ý","Þ","Æ","Ö","á","ð","é","í","ó","ú","ý","þ","æ","ö"},{"Icelandic"}));
    idioms.push_back(idiom({"Á","É","Í","Ó","Ö","Ő","Ú","Ü","Ű","á","é","í","ó","ö","ő","ú","ü","ű"},{"Hungarian"}));
    idioms.push_back(idiom({"À","Ç","É","È","Í","Ó","Ò","Ú","Ü","Ï","à","ç","é","è","í","ó","ò","ú","ü","ï","·",""},{"Catalan"}));
    idioms.push_back(idiom({"À","Â","Æ","Ç","É","È","Ê","Î","Ï","Ô","Œ","Ù","Û","à","â","æ","ç","é","è","ê","î","ï","ô","œ","ù","û"},{"French"}));
    
    idioms.push_back(idiom({"Á","À","Ç","É","È","Í","Ó","Ò","Ú","Ë","Ü","Ï","á","à","ç","é","è","í","ó","ò","ú","ë","ü","ï"},{"Occitan"}));
    idioms.push_back(idiom({"Á","É","Í","Ó","Ú","Â","Ê","Ô","À","ã","õ","ç","á","é","í","ó","ú","â","ê","ô","à"},{"Portuguese"}));
    idioms.push_back(idiom({"Á","É","Í","Ó","Ú","Â","Ê","Ô","À","ã","õ","ç","á","é","í","ó","ú","â","ê","ô","à","ü"},{"Brasileiro"}));
    idioms.push_back(idiom({"á","é","í","ñ","Ñ","ó","ú","ü¡","¿"},{"Spanish"}));
    idioms.push_back(idiom({"à","é","è","ì","ò","ù"},{"Italian"}));
    idioms.push_back(idiom({"Á","É","Í","Ó","Ú","Ý","Ã","Ẽ","Ĩ","Õ","Ũ","Ỹ","Ñ","G","̃","á","é","í","ó","ú","ý","ã","ẽ","ĩ","õ","ũ","ỹ","ñ","g","̃",""},{"Guarani"}));
    idioms.push_back(idiom({"Á","Ą","Ą","́","É","Ę","Ę","́","Í","Į","Į","́","Ł","Ńá","ą","ą","́","é","ę","ę","́","í","į","į","́","ł","ń",""},{"Southern_Athabaskan_anguages"}));
    idioms.push_back(idiom({"’","Ó","Ǫ","Ǫ","́ā","ą","̄","ē","ę","̄","ī","į","̄","ó","ō","ǫ","ǫ","́","ǭ","ú","ū",""},{"Western_Apache"}));
    idioms.push_back(idiom({"'","Ó","Ǫ","Ǫ","́ó","ǫ","ǫ","́"},{"Navajo"}));
    idioms.push_back(idiom({"’","Ú","Ų","Ų","́ú","ų","ų","́"},{"Chiricahua/Mescalero"}));
    idioms.push_back(idiom({"ą","ł","ń","ó","ż"},{"Lechitic_languages"}));
    idioms.push_back(idiom({"ć","ę","ś","ź"},{"Polish"}));
    idioms.push_back(idiom({"ć","ś","ů","ź"},{"Silesian"}));
    idioms.push_back(idiom({"ã","é","ë","ò","ô","ù"},{"Kashubian"}));
    idioms.push_back(idiom({"AĄÃBCDEÉËF","G","H","I","J","K","L","Ł","M","N","Ń","O","Ò","Ó","Ô","P","R","S","T","U","Ù","W","Y","Z","Ż"},{"Kashubian"}));
    idioms.push_back(idiom({"Č","Š","Ž"},{"Slovene"}));
    idioms.push_back(idiom({"Ć","Đ"},{"Bosnian","Croatian","SerbianLatin"}));
    idioms.push_back(idiom({"Á","Ď","É","Ě","Ň","Ó","Ř","Ť","Ú","Ů","Ý","á","ď","é","ě","ň","ó","ř","ť","ú","ů","ý"},{"Czech"}));
    idioms.push_back(idiom({"Á","Ä","Ď","É","Í","Ľ","Ĺ","Ň","Ó","Ô","Ŕ","Ť","Ú","Ý","á","ä","ď","é","í","ľ","ĺ","ň","ó","ô","ŕ","ť","ú","ý"},{"Slovak"}));
    idioms.push_back(idiom({"Ā","Ē","Ģ","Ī","Ķ","Ļ","Ņ","Ō","Ŗ","Ū","ā","ē","ģ","ī","ķ","ļ","ņ","ō","ŗ","ū"},{"Latvian"}));
    idioms.push_back(idiom({"Ą","Ę","Ė","Į","Ų","Ū","ą","ę","ė","į","ų","ū"},{"Lithuanian"}));
    idioms.push_back(idiom({"Đ","À","Ả","Ã","Á","Ạ","Ă","Ằ","Ẳ","Ẵ","Ắ","Ặ","Â","Ầ","Ẩ","Ẫ","Ấ","Ậ","È","Ẻ","Ẽ","É","Ẹ","Ê","Ề","Ể","Ễ","Ế","Ệ","Ì","Ỉ","Ĩ","Í","Ị","Ò","Ỏ","Õ","Ó","Ọ","Ô","Ồ","Ổ","Ỗ","Ố","Ộ","Ơ","Ờ","Ở","Ỡ","Ớ","Ợ","Ù","Ủ","Ũ","Ú","Ụ","Ư","Ừ","Ử","Ữ","Ứ","Ự","Ỳ","Ỷ","Ỹ","Ý","Ỵ","đ","à","ả","ã","á","ạ","ă","ằ","ẳ","ẵ","ắ","ặ","â","ầ","ẩ","ẫ","ấ","ậ","è","ẻ","ẽ","é","ẹ","ê","ề","ể","ễ","ế","ệ","ì","ỉ","ĩ","í","ị","ò","ỏ","õ","ó","ọ","ồ","ổ","ỗ","ố","ơ","ờ","ở","ỡ","ớ","ợ","ù","ủ","ũ","ú","ụ","ư","ừ","ử","ữ","ứ","ự","ỳ","ỷ","ỹ","ý","ỵ"},{"Vietnamese"}));
    idioms.push_back(idiom({"āēīōū"},{"Japanese","","Hawaiian","Māori"}));
    idioms.push_back(idiom({"é"},{"Sundanese"}));
    
    return idioms;
}

