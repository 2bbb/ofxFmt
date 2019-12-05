//
//  ofxFmt.h
//  example
//
//  Created by 2bit on 2019/12/02.
//

#ifndef ofxFmt_h
#define ofxFmt_h

#include <fmt/core.h>

namespace ofxFmt {
    struct basic_parser {
        std::string given_format{""};
        template <typename Context>
        typename Context::iterator parse(Context &ctx) {
            auto it = std::find(ctx.begin(), ctx.end(), '}');
            std::copy(ctx.begin(), it, std::back_inserter(given_format));
            return it;
        };
        
        inline std::string create_format(const char * const meta_format) const
        { return fmt::format(meta_format, given_format); };
    };
};

#define FORMAT_ELEM_1 "{{:{0}}}"
#define FORMAT_ELEM_2 "{{:{0}}}, {{:{0}}}"
#define FORMAT_ELEM_3 "{{:{0}}}, {{:{0}}}, {{:{0}}}"
#define FORMAT_ELEM_4 "{{:{0}}}, {{:{0}}}, {{:{0}}}, {{:{0}}}"

namespace fmt {
    template <>
    struct formatter<ofVec2f> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofVec2f &v, Context &ctx) {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_2),
                             v.x, v.y);
        }
    };

    template <>
    struct formatter<ofVec3f> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofVec3f &v, Context &ctx)
        {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_3),
                             v.x, v.y, v.z);
            
        }
    };

    template <>
    struct formatter<ofVec4f> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofVec4f &v, Context &ctx)
        {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_4),
                             v.x, v.y, v.z, v.w);
            
        }
    };

    template <>
    struct formatter<ofQuaternion> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofQuaternion &q, Context &ctx)
        {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_4),
                             q.x(), q.y(), q.z(), q.w());
        }
    };

    template <>
    struct formatter<ofRectangle> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofRectangle &v, Context &ctx)
        {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_4),
                             v.x, v.y, v.width, v.height);
        }
    };

    template <typename type>
    struct formatter<ofColor_<type>> : ofxFmt::basic_parser {
        template <typename Context>
        typename Context::iterator format(const ofColor_<type> &c, Context &ctx)
        {
            return format_to(ctx.out(),
                             create_format(FORMAT_ELEM_4),
                             c.r, c.g, c.b, c.a);
        }
    };

#ifdef GLM_VERSION
#   if GLM_VERSION < 990
#       define GLM_FORMATTER(VEC_T, FORMAT, ...)\
    template <typename T, glm::precision Q>\
    struct formatter<glm::VEC_T<T, Q>> : ofxFmt::basic_parser {\
        template <typename Context>\
        typename Context::iterator format(const glm::VEC_T<T, Q> &v, Context &ctx)\
        {\
            return format_to(ctx.out(),\
                             create_format(FORMAT),\
                             __VA_ARGS__);\
        }\
    };

    GLM_FORMATTER(tvec1, FORMAT_ELEM_1, v.x);
    GLM_FORMATTER(tvec2, FORMAT_ELEM_2, v.x, v.y);
    GLM_FORMATTER(tvec3, FORMAT_ELEM_3, v.x, v.y, v.z);
    GLM_FORMATTER(tvec4, FORMAT_ELEM_4, v.x, v.y, v.z, v.w);

#   else // GLM_VERSION < 990
#       define GLM_FORMATTER(N, FORMAT, ...)\
    template <typename T, glm::qualifier Q>\
    struct formatter<glm::vec<N, T, Q>> : ofxFmt::basic_parser {\
        template <typename Context>\
        typename Context::iterator format(const glm::vec<N, T, Q> &v, Context &ctx)\
        {\
            return format_to(ctx.out(),\
                             create_format(FORMAT),\
                             __VA_ARGS__);\
        }\
    };

    GLM_FORMATTER(1ul, FORMAT_ELEM_1, v.x);
    GLM_FORMATTER(2ul, FORMAT_ELEM_2, v.x, v.y);
    GLM_FORMATTER(3ul, FORMAT_ELEM_3, v.x, v.y, v.z);
    GLM_FORMATTER(4ul, FORMAT_ELEM_4, v.x, v.y, v.z, v.w);

#   endif

#   ifdef GLM_FORMATTER
#       undef GLM_FORMATTER
#   endif
#endif

};

#endif /* ofxFmt_h */
