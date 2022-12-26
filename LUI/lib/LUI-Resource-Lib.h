#ifndef LuiResource_H
#define LuiResource_H



namespace LuiResource
{

	class Resource {
	public:
		static Resource* getInstance() {
			static Resource instance;
			return &instance;
		}
		char* getResource(int id, int& size);
	private:
		Resource() {}
	};
}

#endif