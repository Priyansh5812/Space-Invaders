#pragma once
#include <raylib.h>
#include <raymath.h>
#include <ECSManager.h>
#include <Constants.h>
#include <utility>
#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <memory>
class ComponentBase;


class EntityBase
{
	public:
		EntityBase();
		virtual ~EntityBase();

	public:
		const Vector3& GetPosition();
		void AddPosition(const Vector3& position);
		
	public:
		virtual void OnCreated() = 0;
		virtual void OnDestroyed() = 0;


	public:
		template<typename T>
		std::shared_ptr<T> TryAddComponent();
		template<typename T>
		std::shared_ptr<T> TryGetComponent();
		template<typename T>
		void TryRemoveComponent();

	protected:
		int globalEntityIndex = -1;
		Matrix Transform;
		Vector3 m_position = { 0,0,0 };
		Vector3 m_rotation = { 0,0,0 };
		Vector3 m_scale = { 1,1,1 };
		void InitializeTransform();
		void RegisterEntity();
		
};




template<typename T>
std::shared_ptr<T> EntityBase::TryAddComponent()
{
	try
	{
		return ECSManager::RegisterComponent<T>(this).second;
	}
	catch (const std::runtime_error& error)
	{
		std::cout << "Caught exception while creating component of type : " << typeid(T).name() << std::endl;
		std::cout << "Reason : " << error.what() << std::endl;
		return nullptr;
	}
}

template<typename T>
void EntityBase::TryRemoveComponent()
{
	try
	{
		ECSManager::UnregisterComponent<T>(this);
	}
	catch (const std::runtime_error& error)
	{
		std::cout << "Caught exception while removing component of type : " << typeid(T).name() << std::endl;
		std::cout << "Reason : " << error.what() << std::endl;
	}
}

template<typename T>
std::shared_ptr<T> EntityBase::TryGetComponent()
{
	try
	{
		return ECSManager::GetComponent<T>(this);
	}
	catch (const std::runtime_error& error)
	{
		std::cout << "Caught exception while getting component of type : " << typeid(T).name() << std::endl;
		std::cout << "Reason : " << error.what() << std::endl;
	}
}



class Entity : public EntityBase
{
public:
	Entity() : EntityBase()
	{
		
	}

public:
	virtual void OnCreated() override
	{
		std::cout << "Entity Created" << std::endl;
	}
	virtual void OnDestroyed() override
	{
		std::cout << "Entity Destroyed" << std::endl;
	}

public:
	~Entity()
	{
		
	}

};

