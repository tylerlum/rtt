/***************************************************************************
  tag: The SourceWorks  Tue Sep 7 00:55:18 CEST 2010  PartDataSource.hpp

                        PartDataSource.hpp -  description
                           -------------------
    begin                : Tue September 07 2010
    copyright            : (C) 2010 The SourceWorks
    email                : peter@thesourceworks.com

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public                   *
 *   License as published by the Free Software Foundation;                 *
 *   version 2 of the License.                                             *
 *                                                                         *
 *   As a special exception, you may use this file as part of a free       *
 *   software library without restriction.  Specifically, if other files   *
 *   instantiate templates or use macros or inline functions from this     *
 *   file, or you compile this file and link it with other files to        *
 *   produce an executable, this file does not by itself cause the         *
 *   resulting executable to be covered by the GNU General Public          *
 *   License.  This exception does not however invalidate any other        *
 *   reasons why the executable file might be covered by the GNU General   *
 *   Public License.                                                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public             *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef ORO_PARTDATASOURCE_HPP_
#define ORO_PARTDATASOURCE_HPP_

#include "DataSource.hpp"
#include "carray.hpp"

namespace RTT
{
    namespace internal
    {
        /**
         * A DataSource which is used to manipulate a reference to a
         * part of a data source.
         *
         * This data source only works on a fixed reference in memory of
         * a given data sequence (ie an element of a top level struct).
         * In case the part's place in memory
         * varies, you need the OffsetPartDataSource, which can access
         * an element at any offset from a given memory location.
         *
         * @param T The data type of an element.
         */
        template<typename T>
        class PartDataSource
        : public AssignableDataSource<T>
        {
            // a reference to a value_t
            typename AssignableDataSource<T>::reference_t mref;
            // parent data source, for updating after set().
            base::DataSourceBase::shared_ptr mparent;
        public:
            ~PartDataSource() {}

            typedef boost::intrusive_ptr<PartDataSource<T> > shared_ptr;

            /**
             * The part is constructed from a reference to a member variable of an existing struct.
             *
             * @param ref    Reference to the struct's variable.
             * @param parent A data source holding the struct.
             */
            PartDataSource( typename AssignableDataSource<T>::reference_t ref,
                            base::DataSourceBase::shared_ptr parent )
                : mref(ref), mparent(parent)
            {
            }

            typename DataSource<T>::result_t get() const
            {
                return mref;
            }

            typename DataSource<T>::result_t value() const
            {
                return mref;
            }

            void set( typename AssignableDataSource<T>::param_t t )
            {
                mref = t;
                updated();
            }

            typename AssignableDataSource<T>::reference_t set()
            {
                return mref;
            }

            typename AssignableDataSource<T>::const_reference_t rvalue() const
            {
                return mref;
            }

            void updated() {
                mparent->updated();
            }

            virtual PartDataSource<T>* clone() const {
                return new PartDataSource<T>(mref, mparent);
            }

            virtual PartDataSource<T>* copy( std::map<const base::DataSourceBase*, base::DataSourceBase*>& replace ) const {
                // if somehow a copy exists, return the copy, otherwise return this (see Attribute copy)
                if ( replace[this] != 0 ) {
                    assert ( dynamic_cast<PartDataSource<T>*>( replace[this] ) == static_cast<PartDataSource<T>*>( replace[this] ) );
                    return static_cast<PartDataSource<T>*>( replace[this] );
                }
                // Other pieces in the code rely on insertion in the map :
                replace[this] = new PartDataSource<T>(mref, mparent->copy(replace));
                // return this instead of a copy.
                return static_cast<PartDataSource<T>*>(replace[this]);

            }
        };

        template<typename T>
        class PartDataSource< carray<T> >
        : public AssignableDataSource< carray<T> >
        {
            // keeps ref to real array.
            carray<T> mref;
            // parent data source, for updating after set().
            base::DataSourceBase::shared_ptr mparent;
        public:
            ~PartDataSource() {}

            typedef boost::intrusive_ptr<PartDataSource<T> > shared_ptr;

            /**
             * The part is constructed from a reference to a member variable of an existing struct.
             *
             * @param ref    Reference to the struct's variable.
             * @param parent A data source holding the struct.
             */
            PartDataSource( carray<T> ref,
                            base::DataSourceBase::shared_ptr parent )
                : mref(ref), mparent(parent)
            {
            }

            carray<T> get() const
            {
                return mref;
            }

            carray<T> value() const
            {
                return mref;
            }

            void set( typename AssignableDataSource< carray<T> >::param_t t )
            {
                mref = t;
                updated();
            }

            carray<T>& set()
            {
                return mref;
            }

            carray<T> const& rvalue() const
            {
                return mref;
            }

            void updated() {
                mparent->updated();
            }

            virtual PartDataSource* clone() const {
                return new PartDataSource(mref, mparent);
            }

            virtual PartDataSource* copy( std::map<const base::DataSourceBase*, base::DataSourceBase*>& replace ) const {
                // if somehow a copy exists, return the copy, otherwise return this (see Attribute copy)
                if ( replace[this] != 0 ) {
                    assert ( dynamic_cast<PartDataSource*>( replace[this] ) == static_cast<PartDataSource*>( replace[this] ) );
                    return static_cast<PartDataSource*>( replace[this] );
                }
                // Other pieces in the code rely on insertion in the map :
                replace[this] = new PartDataSource(mref, mparent->copy(replace));
                // return this instead of a copy.
                return static_cast<PartDataSource*>(replace[this]);

            }
        };
    }
}


#endif /* ORO_PARTDATASOURCE_HPP_ */
