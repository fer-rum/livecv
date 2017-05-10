#ifndef QDOCUMENTQMLOBJECTS_H
#define QDOCUMENTQMLOBJECTS_H

#include "qqmljsparserglobal.h"
#include <QList>

namespace QmlJS{ namespace AST {
    class Node;
}}

namespace lcv{

class QDocumentQmlValueObjectsVisitor;

class Q_QMLJSPARSER_EXPORT QDocumentQmlValueObjects{

public:
    friend class QDocumentQmlValueObjectsVisitor;

    class RangeObject;
    class RangeProperty;

    class RangeItem{
    public:
        virtual ~QRangeItem(){}

        virtual QmlJS::AST::Node* getAst() = 0;
        virtual RangeItem* getParent() = 0;
        virtual void appendObject(RangeObject* child) = 0;
        virtual void appendProperty(RangeProperty*){}

    };

    class RangeProperty : public RangeItem{

    public:
        RangeProperty() : ast(0), parent(0), child(0), begin(0), propertyEnd(0), valueBegin(0), end(0){}
        ~RangeProperty(){}

        void appendObject(RangeObject* object){ child = object; }
        QmlJS::AST::Node* getAst(){ return ast; }
        RangeItem* getParent(){ return parent; }
        QStringList name() const;
        QStringList object() const;
        QString type() const;
        bool hasType() const;

    public:
        QmlJS::AST::Node* ast;

        RangeItem* parent;
        RangeObject* child;

        int begin;
        int propertyEnd;
        int valueBegin;
        int end;
    };

    class RangeObject : public RangeItem{

    public:
        RangeObject() : ast(0), parent(0), begin(0), end(0){}
        ~RangeObject(){
            for ( int i = 0; i < children.size(); ++i )
                delete children[i];
        }

        void appendObject(RangeObject *child) { children.append(child); }
        void appendProperty(RangeProperty *property){ properties.append(property); }
        QmlJS::AST::Node* getAst(){ return ast; }
        RangeItem* getParent(){ return parent; }

    public:
        QmlJS::AST::Node* ast;

        RangeItem* parent;
        QList<RangeObject*>   children;
        QList<RangeProperty*> properties;

        int begin;
        int end;
    };

public:
    QDocumentQmlValueObjects();
    ~QDocumentQmlValueObjects();

    RangeObject* root();

    QString toString() const;

    void visit(QmlJS::AST::Node* astroot);

    QList<RangeProperty*> propertiesBetween(int start, int end, RangeObject* root = 0);

private:
    QString toStringRecursive(RangeObject* object, int indent = 0) const;
    QString toStringRecursive(RangeProperty* property, int indent = 0) const;
    QDocumentQmlValueObjects::RangeObject* appendRange(QmlJS::AST::Node* ast, int begin, int end);

    RangeObject* m_root;
};

inline QDocumentQmlValueObjects::RangeObject *QDocumentQmlValueObjects::root(){
    return m_root;
}

}// namespace

#endif // QDOCUMENTQMLOBJECTS_H