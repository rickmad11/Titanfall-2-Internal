#include "pch.h"

#include "Engines/Source Engine/Interface Manager/Interface Manager.h"

namespace MadFramework::NetVarManager
{
	int NetVarOffset(RecvTable* pRecvTable, const char* NetVarName)
	{
		for (int i = 0; i < pRecvTable->m_nProps; i++)
		{
			RecvProp* pRecvProp = pRecvTable->m_pProps[i];

			if (strcmp(pRecvProp->m_pVarName, NetVarName) == 0)
				return pRecvProp->get_offset();

			RecvTable* pNextRecvTable = pRecvProp->GetDataTable();
			
			if (pRecvProp->GetType() == DPT_DataTable && pNextRecvTable)
			{
				int currNetVarOffset = NetVarOffset(pNextRecvTable, NetVarName);
			
				if (currNetVarOffset != 0)
					return currNetVarOffset + pRecvProp->get_offset();
			}
		}

		return 0;
	}

	int GetNetVar(const char* TableName, const char* NetVarName)
	{
		ClientClass* pClientClass = MadFramework::InterfaceManager::GetInterface<IBaseClientDLL>()->GetAllClasses();
		for (ClientClass* curr = pClientClass; curr; curr = curr->m_pNext)
		{
			if (strcmp(TableName, curr->m_pNetworkName) == 0)
				return NetVarOffset(curr->m_pRecvTable, NetVarName);
		}

		return 0;
	}

	void ConsoleDump()
	{
		auto next_dump = [](this auto& self, RecvTable* pRecvTable, int level) -> void
		{
				for (int i = 0; i < pRecvTable->m_nProps; i++)
				{
					RecvProp* pRecvProp = pRecvTable->m_pProps[i];

					if (isdigit(*pRecvProp->GetName()))
						continue;

					for (size_t j = 0; j < level; j++)
						std::cout << " ";

					DVariant variant {};
					variant.m_Type = pRecvProp->GetType();

					std::printf("%03d. + %04x %s %s \n", i, pRecvProp->get_offset(), pRecvProp->GetName(), variant.ToString().c_str());

					RecvTable* pNextRecvTable = pRecvProp->GetDataTable();

					if (pRecvProp->GetType() == DPT_DataTable && pNextRecvTable)
						self(pNextRecvTable, level + 1);
				}
		};

		ClientClass* pClientClass = MadFramework::InterfaceManager::GetInterface<IBaseClientDLL>()->GetAllClasses();

		for (ClientClass* curr = pClientClass; curr; curr = curr->m_pNext)
		{
			std::printf("\n\nClass: %s ID: %i\n", curr->m_pNetworkName, curr->m_ClassID);
			next_dump(curr->m_pRecvTable, 0);
		}
	}
}
