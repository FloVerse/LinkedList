struct _Rules
{
  unsigned int size;			///< number of rules
  Rule *rule;				    ///< rules array
};

struct _Rule
{
  unsigned int size_premise;	///< number of premises
  unsigned int size_conclusion;	///< number of conclusion
  unsigned int *premise;		///< premise array
  unsigned int *conclusion;		///< conclusion array
};

struct _Facts
{
  unsigned int size;			///< number of facts
  unsigned int *fact;			///< facts array
};
