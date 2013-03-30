Variable::Variable () {

	varType = new std::string [4] ;
	typeNum = 4 ;
	varType[1] = "int";
	varType[2] = "float";
	varType[3] = "char";
	varType[4] = "string";

}


//get methods

int Variable::getIntValue (std::string name ) {

	int i = 0 ;
	while ( i < intValue.size() ) {
		if ( intValueName [i] == name ) {
			return intValue [i] ;
		}
		i++ ;
	}
	return -2001 ; // if the variable not found 	

}
float Variable::getFloatValue (std::string name ) {

	int i = 0 ;
	while ( i < floatValue.size() ) {
		if ( floatValueName [i] == name ) {
			return floatValue [i] ;
		}
		i++ ;
	}
	return -2001.2001 ; // if the variable not found
	
}
char Variable::getCharValue (std::string name ) {

	int i = 0 ;
	while ( i < charValue.size() ) {
		if ( charValueName [i] == name ) {
			return charValue [i] ;
		}
		i++ ;
	}
	return '\0' ; // if the variable not found 

}
std::string Variable::getStringValue (std::string name ) {

	int i = 0 ;
	while ( i < stringValue.size() ) {
		if ( stringValueName [i] == name ) {
			return stringValue [i] ;
		}
		i++ ;
	}
	return NULL ;

}

int Variable::getTypeNum ( ) {

	return typeNum ;
}

//set methods

bool Variable::setIntValue (std::string name , int value ) {

	int i = 0 ;
	while ( i < intValue.size() ) {
		if ( intValueName [i] == name ) {
			intValue [i]  =  value ;
			return true ;
		}
		i++ ;
	}
	return false ;

}
bool Variable::setFloatValue  (std::string name , float value ) {

	int i = 0 ;
	while ( i < floatValue.size() ) {
		if ( floatValueName [i] == name ) {
			floatValue [i] = value ;
			return true ;
		}
		i++ ;
	}
	return false ;

}
bool Variable::setCharValue (std::string name , char value ) {

	int i = 0 ;
	while ( i < charValue.size() ) {
		if ( charValueName [i] == name ) {
			charValue [i] = value ;
			return true ;
		}
		i++ ;
	}
	return false ;

}
bool Variable::setStringValue (std::string name , std::string value ) {

	int i = 0 ;
	while ( i < stringValue.size() ) {
		if ( stringValueName [i] == name ) {
			stringValue [i] = value ;
			return true ;
		}
		i++ ;
	}
	return false ;

}

//tool methods

bool Variable::addIntValue (std::string name , int value ) {

	if ( isMultiDef ( name ) ) 
		return false ;
	intValue.push_back (value ) ;
	intValueName.push_back (name ) ;
	return true ;

}
bool Variable::addFloatValue (std::string name , float value ) {

	if ( isMultiDef ( name ) ) 
		return false ;
	floatValue.push_back (value ) ;
	floatValueName.push_back (name ) ;
	return true ;

}
bool Variable::addCharValue (std::string name , char value ) {

	if ( isMultiDef ( name ) ) 
		return false ;
	charValue.push_back (value ) ;
	charValueName.push_back (name ) ;
	return true ;

}
bool Variable::addStringValue (std::string name , std::string value ) {

	if ( isMultiDef ( name ) ) 
		return false ;
	stringValue.push_back (value ) ;
	stringValueName.pushBack (name ) ;
	return true ;

}
bool Variable::isMultiDef (std::string name ) {

	int i = 0 ;
	while ( i < intValueName.size() ) {
		if (intValueName[i] == name )
			return true ;
		i++ ;
	}
	i = 0 ;
	while ( i < floatValueName.size() ) {
		if (floatValueName[i] == name )
			return true ;
		i++ ;
	}
	i = 0 ;
	while ( i < charValueName.size() ) {
		if (charValueName[i] == name )
			return true ;
		i++ ;
	}
	i = 0 ;
	while ( i < stringValueName.size() ) {
		if (stringValueName[i] == name )
			return true ;
		i++ ;
	}
	return false ;

}
std::String Variable::getType (std::sting name ) {

	int i = 0 ;
	while ( i < intValueName.size() ) {
		if (intValueName[i] == name )
			return "INT" ;
		i++ ;
	}
	i = 0 ;
	while ( i < floatValueName.size() ) {
		if (floatValueName[i] == name )
			return "FLOAT" ;
		i++ ;
	}
	i = 0 ;
	while ( i < charValueName.size() ) {
		if (charValueName[i] == name )
			return "CHAR" ;
		i++ ;
	}
	i = 0 ;
	while ( i < stringValueName.size() ) {
		if (stringValueName[i] == name )
			return "STRING" ;
		i++ ;
	}
	return NULL ;
	
}
std::string Variable::type ( int i ) {

	return varType [i] ;
}
