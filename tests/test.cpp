#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../datastructures/Environment.h"

TEST_CASE("Environment Basics"){
    Environment env = Environment(10, 5, 42, true, -0.01);
    REQUIRE(env.height == 10);
    REQUIRE(env.width == 5);
    REQUIRE(env.start != env.end);
    REQUIRE(env.observable_states.size() == 50);
}

TEST_CASE("Environment Generation: Deterministic"){
    Environment env = Environment(10, 5, 42, true,-0.01);
    SECTION("edge state (0, 0)"){
        std::tuple<int, int> edge_state (0, 0);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go to the left
        int action = 3;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (0, 0)"){
        std::tuple<int, int> edge_state (0, 0);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go to the left
        int action = 0;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }

    SECTION("edge state (9, 4)"){
        std::tuple<int, int> edge_state (9, 4);
        std::tuple<std::tuple<int, int>, float> edge_state_reward (edge_state, env.living_reward);
        // go up
        int action = 0;
        std::map <std::tuple<std::tuple<int, int>, float>, float> state_reward_prob = env.p(edge_state, action);
        // can only be one next state since it's a deterministic environment
        REQUIRE(state_reward_prob.size() == 1);
        // the next state should be the current state
        REQUIRE(state_reward_prob.begin()->first == edge_state_reward);
        // probability should be 100% (deterministic)
        REQUIRE(state_reward_prob.begin()->second == 1.0);
    }
}

