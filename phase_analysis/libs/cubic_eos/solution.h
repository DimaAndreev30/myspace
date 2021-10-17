#pragma once

#include <string>


namespace MySpace::PhAn::EoS {
    
    class Solution {
    public:
        enum Status {
            OK,
            POSITIVE_P_NO_ROOTS,
            POSITIVE_P_TWO_ROOTS,
            NEGATIVE_P_ONE_ROOT,
            NEGATIVE_P_THREE_ROOTS
        };
        
    public:
        Solution(Status status = OK)
            : status_(status)
            , smaller_(0)
            , bigger_(0)
            , isTwoPhases_(false)
            , isSolution_(false)
        {
        }
        
        Solution(double solution, Status status = OK)
            : status_(status)
            , smaller_(solution)
            , bigger_(solution)
            , isTwoPhases_(false)
            , isSolution_(true)
        {
        }
        
        Solution(double smaller, double bigger, Status status = OK)
            : status_(status)
            , smaller_(smaller)
            , bigger_(bigger)
            , isTwoPhases_(true)
            , isSolution_(true)
        {
        }
            
        bool isSolution() const {
            return isSolution_;
        }
        
        bool isTwoPhases() const {
            return isTwoPhases_;
        }
        
        double getL() const {
            return smaller_;
        }
        
        double getV() const {
            return bigger_;
        }
        
        double isOk() const {
            return status_ == OK;
        }
        
        Status getStatus() const {
            return status_;
        }
        
        std::string getStatusAsString() const {
            switch (status_) {
                case OK:
                    return "ok";
                case POSITIVE_P_NO_ROOTS:
                    return "positive P with no roots";
                case POSITIVE_P_TWO_ROOTS:
                    return "positive P with two roots";
                case NEGATIVE_P_ONE_ROOT:
                    return "negative P with one root";
                case NEGATIVE_P_THREE_ROOTS:
                    return "negative P with three roots";
                default:
                    return "unknown status";
            }
        }
        
    private:
        Status status_;
        
        double smaller_, bigger_;
        bool isTwoPhases_;
        bool isSolution_;
    };
    
} // namespace MySpace::PhAn::EoS;