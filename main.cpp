// Sean Parent polymorphism without inheritance lecture 

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <ostream>
#include <string>
#include <assert.h>

template<typename T>
void draw(const T& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << x << std::endl;
}

class object_t
{
public:

    template<typename T>
    object_t(T x) : self_(std::make_shared<model<T>>(std::move(x)))
    {
    }

    friend void draw(const object_t& x, std::ostream& out, size_t position)
    {
        x.self_->draw_(out, position);      
    }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;        
        virtual void draw_(std::ostream&, size_t) const = 0;
    }; 

    template<typename T>
    struct model final : concept_t
    {
        model(T x) : data_(std::move(x))
        {
        }

        void draw_(std::ostream& out, size_t position) const override
        {
            draw(data_, out, position);
        }

        T data_;
    };

    std::shared_ptr<const concept_t> self_;
}; 

using document_t = std::vector<object_t>;
using history_t = std::vector<document_t>;

void draw(const document_t& x, std::ostream& out, size_t position)
{
    out << std::string(position, ' ') << "<document>" << std::endl;

    for (const auto& e: x) {
        draw(e, out, position + 2);
    }

    out << std::string(position, ' ') << "</document>" << std::endl; 
}

class my_class_t
{
    friend std::ostream& operator<<(std::ostream& out, const my_class_t& x)
    {
        out << "my_class_t";
        return out;
    }
};

void commit(history_t& x)
{
    assert(x.size());
    x.push_back(x.back());
}

void undo(history_t& x)
{
    assert(x.size());
    x.pop_back();
}

document_t& current(history_t& x)
{
    assert(x.size());
    return x.back();
}

int main(int argc, char** argv)
{
/*  document_t document;

    document.emplace_back(0); 
    document.emplace_back(std::string("Hello!")); 
    document.emplace_back(document); 
    document.emplace_back(my_class_t());

    draw(document, std::cout, 0);
*/

    history_t h(1);

    current(h).emplace_back(0);
    current(h).emplace_back(std::string("Hello!"));

    draw(current(h), std::cout, 0);
    std::cout << "----------------------------------------" << std::endl;

    commit(h);

    current(h)[0] = 42.5;
    current(h)[1] = std::string("World");
    current(h).emplace_back(current(h));
    current(h).emplace_back(my_class_t());
 
    draw(current(h), std::cout, 0);
    std::cout << "----------------------------------------" << std::endl;

    undo(h);
    draw(current(h), std::cout, 0);
}







/*
    document_t document;

    document.emplace_back(0); 
    document.emplace_back(std::string("Hello!")); 
    document.emplace_back(document); 
    document.emplace_back(my_class_t());

    draw(document, std::cout, 0);


    object_t(const object_t& x) : self_(x.self_->copy_())
    {
        std::cout << "copy" << std::endl;    
    }

    object_t(object_t&&) noexcept = default;        

    object_t& operator=(object_t& x) noexcept
    {
       return *this = object_t(x);
    }

    virtual std::unique_ptr<concept_t> copy_() const = 0;
    object_t& operator=(object_t&&) noexcept = default;

        std::unique_ptr<concept_t> copy_() const override
        {
            return std::make_unique<model>(*this);        
        }


*/
