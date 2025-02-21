#pragma once

class RecvProp;
class RecvTable;

typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_Quaternion,
	DPT_Int64,
	DPT_DataTable,
	DPT_NUMSendPropTypes
} SendPropType;

class DVariant
{
public:
	DVariant() { m_Type = DPT_Float; }
	DVariant(float val) { m_Type = DPT_Float; m_Float = val; }

	std::string ToString()
	{
		static char text[128];

		switch (m_Type)
		{
		case DPT_Int:
			sprintf_s(text, sizeof(text), "Int");
			break;
		case DPT_Float:
			sprintf_s(text, sizeof(text), "Float");
			break;
		case DPT_Vector:
			sprintf_s(text, sizeof(text), "Vector");
			break;
		case DPT_Quaternion:
			sprintf_s(text, sizeof(text), "Quaternion");
			break;
		case DPT_String:
			sprintf_s(text, sizeof(text), "String");
			break;
		case DPT_Array:
			sprintf_s(text, sizeof(text), "Array");
			break;
		case DPT_DataTable:
			sprintf_s(text, sizeof(text), "DataTable");
			break;
		case DPT_Int64:
			sprintf_s(text, sizeof(text), "Int64");
			break;
		case DPT_VectorXY:
			sprintf_s(text, sizeof(text), "VectorXY");
			break;
		default:
			sprintf_s(text, sizeof(text), "unknown");
			break;
		}

		return text;
	}

	union
	{
		float	m_Float;
		long	m_Int;
		char* m_pString;
		void* m_pData;	// For DataTables.
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
		float	m_Vector[4];
#else
		float	m_Vector[3];
#endif
	};
	SendPropType	m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp;		// The property it's receiving.

	DVariant		m_Value;			// The value given to you to store.

	int				m_iElement;			// Which array element you're getting.

	int				m_ObjectID;			// The object being referred to.
};

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);

typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);

typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData, int objectID);

class RecvProp
{
public:
	RecvProp();
	void					InitArray(int nElements);
	int						GetNumElements() const;
	void					SetNumElements(int nElements);
	int						GetFlags() const;
	const char* GetName() const;
	SendPropType			GetType() const;
	RecvTable* GetDataTable() const;
	void					SetDataTable(RecvTable* pTable);
	void					SetProxyFn(RecvVarProxyFn fn);
	int						get_offset() const;
	void					SetOffset(int o);
	RecvProp* GetArrayProp() const;
	void					SetArrayProp(RecvProp* pProp);
	bool					IsInsideArray() const;
	void					SetInsideArray();

public:
	SendPropType	m_RecvType;				
	int				m_Offset;				
	int				_unk0x0008;				
	int				_unk0x000C;				
	char			_unk0x0010[0x10];		
	RecvTable*		m_pDataTable;			
	char*			m_pVarName;				
	bool			m_bInsideArray;			
	char			_unk0x0031[0x7];	
	RecvProp*		m_pArrayProp;			
	void*			m_ProxyFn;				
	char			_unk0x0048[0xC];		
	int				m_Flags;				
	char			_unk0x0058[0x4];		
	int				m_nElements;			
	char			_unk0x0060[0x8];		
};

inline void RecvProp::InitArray(int nElements)
{
	m_RecvType = DPT_Array;
	m_nElements = nElements;
}

inline int RecvProp::GetNumElements() const
{
	return m_nElements;
}

inline void RecvProp::SetNumElements(int nElements)
{
	m_nElements = nElements;
}

inline int RecvProp::GetFlags() const
{
	return m_Flags;
}

inline const char* RecvProp::GetName() const
{
	return m_pVarName;
}

inline SendPropType RecvProp::GetType() const
{
	return m_RecvType;
}

inline RecvTable* RecvProp::GetDataTable() const
{
	return m_pDataTable;
}

inline void RecvProp::SetDataTable(RecvTable* pTable)
{
	m_pDataTable = pTable;
}

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
{
	m_ProxyFn = fn;
}

inline int RecvProp::get_offset() const
{
	return m_Offset;
}

inline void RecvProp::SetOffset(int o)
{
	m_Offset = o;
}

inline RecvProp* RecvProp::GetArrayProp() const
{
	return m_pArrayProp;
}

inline void RecvProp::SetArrayProp(RecvProp* pProp)
{
	m_pArrayProp = pProp;
}

inline bool RecvProp::IsInsideArray() const
{
	return m_bInsideArray;
}

inline void RecvProp::SetInsideArray()
{
	m_bInsideArray = true;
}
