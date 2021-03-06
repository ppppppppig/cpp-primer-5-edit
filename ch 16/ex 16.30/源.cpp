#include "Head.h"
#include "date.h"
#include "Sales_data.h"
#include "��������.h"
#include "Strblob.h"
#include "StrBlobPtr.h"
#include "Experiment.h"
#include "Employee.h"
#include "TreeNode.h"
#include "HasPtr.h"
#include "StrVec.h"
#include "String.h"
#include "Foo.h"
#include "Quote.h"
#include "Bulk_quote.h"
#include "Disc_quote.h"
#include "imitation_standard_function.h"
#include "Blob.h"
#include "BlobPtr.h"
#include "Vec.h"
#include "Shared_ptr.h"
#include "unique_ptr.h"
class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr) :os(s) {}
	template <typename T> void operator()(T *b) const{
		os << "deleting unique_ptr" << std::endl;
		delete b;
	}
	~DebugDelete() {}
private:
	std::ostream &os;
};
int main() {
	unique_ptr<int, DebugDelete> T(new int(3), DebugDelete());
	cout << *T << endl;
	return 0;
}