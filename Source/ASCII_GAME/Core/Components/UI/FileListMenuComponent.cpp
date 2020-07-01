#include "FileListMenuComponent.h"
#include "../../GameDatabase/CreationData/UI/FileListMenuComponentCreate.h"

#include <string>
#include <iostream>
#include <filesystem>

FileListMenuComponent::FileListMenuComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner)
:ListMenuComponent(pComponentCreate, pOwner)
{
}

FileListMenuComponent::~FileListMenuComponent()
{
}

void FileListMenuComponent::Initialise()
{
	const FileListMenuComponentCreate* pRomListMenuComponentCreate = dynamic_cast<const FileListMenuComponentCreate*>(m_pCreationData);
	if (pRomListMenuComponentCreate)
	{
		std::string directory = pRomListMenuComponentCreate->m_FileDir;
		std::string fileExtension = pRomListMenuComponentCreate->m_FileExtension;

		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory))
		{
			bool hasExtension = entry.path().filename().has_extension();
			std::string extension = entry.path().filename().extension().string();
			bool extensionMatches = entry.path().filename().extension().compare(fileExtension) == 0;
			if (fileExtension.length() == 0 || hasExtension && extensionMatches)
			{
				MenuItem menuItem;
				menuItem.m_DisplayText = entry.path().filename().stem().string();
				menuItem.m_Payload = entry.path().string();
				m_MenuItems.push_back(menuItem);
			}
		}
	}

	ListMenuComponent::Initialise();
}
